from xmlrpc.client import ServerProxy
import docker
import time
import xmlrpc
from docker.models.containers import Container
import asyncio
from asyncio import TimeoutError, wait_for
from typing import Optional

client = docker.from_env()

def destroy_container(container: Container) -> None:
    container.kill()
    container.remove()

async def container_running(container: Container) -> None:
    sleep_interval = 0.2

    while True:
        # Check if the container is running, then sleep for 0.1 sec
        if client.containers.get(container.id).status == "running":
            return

        # Sleep first to give container some time
        await asyncio.sleep(sleep_interval)

async def container_ready(container: Container) -> None:
    # Wait for the container for start running
    try:
        await wait_for(
            container_running(container), 5 #seconds
        )
    except TimeoutError as e:
        print("Container timed out")
        destroy_container(container)
        raise e

#Create docker containers
def run_new_container(docker_image_tag: str, port: int) -> Container:
    # Create containers
    try:
        # Note: These options are different from test harness, because the network topology is different
        # Test Harness has dedicated network on which we can find containers by hostname
        # This container is launched from the host directly and is bridged, hence we can easily use ports to connect
        mount_volumes = {"/var/run/dbus" : {'bind': '/var/run/dbus', 'mode': 'rw'}}
        return client.containers.run(
            docker_image_tag, detach=True, ports={5000:port}, volumes=mount_volumes, privileged=True
        )
    except Exception as error:
        print(
            "Error ocurred while creating a container from image " + str(error)
        )

def get_shortened_id(self, container: Container) -> str:
    # Docker containers are addressable by first 12 chars of the container id
    # https://github.com/docker/docker-py/issues/2660
    return container.id[:12]

async def create_container(docker_image_tag: str,  port: int) -> Container:
    container = run_new_container(docker_image_tag=docker_image_tag, port=port)
    if container is None:
        print("Unable to run container: " + docker_image_tag)
    await container_ready(container)
    print("Container running for " + docker_image_tag)

    return container

def call_rpc(device_server,  method_name, *params):
    method_list: List = device_server.system.listMethods()  # type: ignore
    if method_name in method_list:
        response_dict = getattr(device_server, method_name)(*params)
        return response_dict['result']
    else:
        raise RuntimeError(f"RPC Method {method_name} is not available.")

async def main():
    try: 
        container_1 = await create_container(docker_image_tag="chip-test", port=5050)
    except AttributeError as e:
        for container in client.containers.list():
            for tag in container.image.tags:
                if tag == "chip-test:latest":
                    print("WARNING:Container already running, killing the container, please try running the script again")
                    destroy_container(container)
                    exit()
    
    print("List of containers: " + str(client.containers.list()))

    # Wait for the controller to start the rpc server
    time.sleep(1)
    
    # Create an RPC server
    server_1 = xmlrpc.client.ServerProxy("http://localhost:5050/")
    discriminator = 3840
    pin_code = 20202021
    node_id = 1234

    # Invoke RPCs
    try: 
        print("Calling RPCs")
        print("echo_alive Response:" + server_1.echo_alive("Test"))
        print(server_1.system.listMethods())
        scan = call_rpc(server_1, "ble_scan")
        print(f"scan: {scan}")
        connect = server_1.ble_connect(discriminator, pin_code, node_id)
        print(f"connect: {connect}")
        pase_data = server_1.get_pase_data()
        print(f"pase_data: {pase_data}")
        fabric_id = server_1.get_fabric_id()
        print(f"fabric_id: {fabric_id}")

        # Network Provisioning commands
        ssid="str:UncharteredTerretory"
        credentials="str:areaaa51"
        zcl_add_network = server_1.zcl_command(
                "NetworkCommissioning",
                "AddWiFiNetwork",
                node_id, 0, 0,
                {
                    'breadcrumb':0,
                    'timeoutMs': 1000,
                    'ssid':ssid,
                    'credentials':credentials
                    }
                )
        print(f"zcl_add_network: {zcl_add_network}")
        zcl_enable_network = server_1.zcl_command(
                "NetworkCommissioning",
                "EnableNetwork",
                node_id,
                0, 0,
                {
                    'breadcrumb':0,
                    'timeoutMs': 1000,
                    'networkID':ssid
                    }
                )
        print(f"zcl_enable_network: {zcl_enable_network}")

        # OnOff ZCL commands
        zcl_on_off = server_1.zcl_command("OnOff", "Toggle", node_id, 1, 0)
        print(f"zcl_on_off: {zcl_on_off}")

        # LevelControl ZCL commands
        zcl_level_control = server_1.zcl_command(
                "LevelControl",
                "MoveToLevel",
                node_id,
                1, 0,
                {
                    'level':50, 
                    'transitionTime':10,
                    'optionMask':10,
                    'optionOverride':10
                    }
                )
        print(f"zcl_level_control: {zcl_level_control}")

        # Read ZCL Basic Attributes
        print("Starting Attribute Read")
        zcl_read_attributes = server_1.zcl_read_attribute(
                "Basic", "ProductID", node_id, 0, 0)
        print(f"zcl_read_attributes_PID: {zcl_read_attributes}")
        zcl_read_attributes_VID = server_1.zcl_read_attribute(
                "Basic", "VendorID", node_id, 0, 0)
        print(f"zcl_read_attributes_VID: {zcl_read_attributes_VID}")
        zcl_read_attributes = server_1.zcl_read_attribute(
                "Basic", "HardwareVersion", node_id, 0, 0)
        print(f"zcl_read_attributes: {zcl_read_attributes}")

    except Exception as e:
        print(e)

    # Cleanup
    destroy_container(container_1)

if __name__ == "__main__":
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main())
    loop.close()
