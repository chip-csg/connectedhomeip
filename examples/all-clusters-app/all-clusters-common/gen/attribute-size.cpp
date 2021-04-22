/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

// THIS FILE IS GENERATED BY ZAP

#include <app/util/af.h>
#include <app/util/basic-types.h>
#include <support/SafeInt.h>
#include <support/logging/CHIPLogging.h>

#include "gen/af-structs.h"

using namespace chip;

// The first 2 bytes specify the number of entries. A value of 0xFFFF means the list in invalid
// and data is undefined.
constexpr uint16_t kSizeLengthInBytes = 2u;

void copyListMember(uint8_t * dest, uint8_t * src, bool write, uint16_t * offset, uint16_t length)
{
    if (write)
    {
        memmove(dest + *offset, src, length);
    }
    else
    {
        memmove(dest, src + *offset, length);
    }

    *offset = static_cast<uint16_t>(*offset + length);
}

uint16_t emberAfCopyList(ClusterId clusterId, EmberAfAttributeMetadata * am, bool write, uint8_t * dest, uint8_t * src,
                         int32_t index)
{
    if (index == -1)
    {
        memmove(dest, src, am->size);
        return am->size;
    }

    if (index == 0)
    {
        if (write)
        {
            // src is a pointer to native-endian uint16_t, dest is pointer to buffer that should hold little-endian value
            emberAfCopyInt16u(dest, 0, *reinterpret_cast<uint16_t *>(src));
        }
        else
        {
            // src is pointer to buffer holding little-endian value, dest is a pointer to native-endian uint16_t
            *reinterpret_cast<uint16_t *>(dest) = emberAfGetInt16u(src, 0, kSizeLengthInBytes);
        }
        return kSizeLengthInBytes;
    }

    if (!chip::CanCastTo<uint16_t>(index))
    {
        ChipLogError(Zcl, "Index %l is invalid. Should be between 1 and 65534", index);
        return 0;
    }

    uint16_t entryLength = 0;
    switch (clusterId)
    {
    case 0x001D: // Descriptor Cluster
    {
        uint16_t entryOffset = kSizeLengthInBytes;
        switch (am->attributeId)
        {
        case 0x0000: // device list
        {
            entryLength = 6;
            if (((index - 1) * entryLength) > (am->size - entryLength))
            {
                ChipLogError(Zcl, "Index %l is invalid.", index);
                return 0;
            }
            entryOffset = static_cast<uint16_t>(entryOffset + ((index - 1) * entryLength));
            // Struct _DeviceType
            _DeviceType * entry = reinterpret_cast<_DeviceType *>(write ? src : dest);
            copyListMember(write ? dest : (uint8_t *) &entry->type, write ? (uint8_t *) &entry->type : src, write, &entryOffset,
                           sizeof(entry->type)); // DEVICE_TYPE_ID
            copyListMember(write ? dest : (uint8_t *) &entry->revision, write ? (uint8_t *) &entry->revision : src, write,
                           &entryOffset, sizeof(entry->revision)); // INT16U
            break;
        }
        case 0x0001: // server list
        {
            entryLength = 2;
            if (((index - 1) * entryLength) > (am->size - entryLength))
            {
                ChipLogError(Zcl, "Index %l is invalid.", index);
                return 0;
            }
            entryOffset = static_cast<uint16_t>(entryOffset + ((index - 1) * entryLength));
            copyListMember(dest, src, write, &entryOffset, entryLength); // CLUSTER_ID
            break;
        }
        case 0x0002: // client list
        {
            entryLength = 2;
            if (((index - 1) * entryLength) > (am->size - entryLength))
            {
                ChipLogError(Zcl, "Index %l is invalid.", index);
                return 0;
            }
            entryOffset = static_cast<uint16_t>(entryOffset + ((index - 1) * entryLength));
            copyListMember(dest, src, write, &entryOffset, entryLength); // CLUSTER_ID
            break;
        }
        case 0x0003: // parts list
        {
            entryLength = 1;
            if (((index - 1) * entryLength) > (am->size - entryLength))
            {
                ChipLogError(Zcl, "Index %l is invalid.", index);
                return 0;
            }
            entryOffset = static_cast<uint16_t>(entryOffset + ((index - 1) * entryLength));
            copyListMember(dest, src, write, &entryOffset, entryLength); // ENDPOINT_ID
            break;
        }
        }
        break;
    }
    case 0xF004: // Group Key Management Cluster
    {
        uint16_t entryOffset = kSizeLengthInBytes;
        switch (am->attributeId)
        {
        case 0x0000: // groups
        {
            entryLength = 6;
            if (((index - 1) * entryLength) > (am->size - entryLength))
            {
                ChipLogError(Zcl, "Index %l is invalid.", index);
                return 0;
            }
            entryOffset = static_cast<uint16_t>(entryOffset + ((index - 1) * entryLength));
            // Struct _GroupState
            _GroupState * entry = reinterpret_cast<_GroupState *>(write ? src : dest);
            copyListMember(write ? dest : (uint8_t *) &entry->VendorId, write ? (uint8_t *) &entry->VendorId : src, write,
                           &entryOffset, sizeof(entry->VendorId)); // INT16U
            copyListMember(write ? dest : (uint8_t *) &entry->VendorGroupId, write ? (uint8_t *) &entry->VendorGroupId : src, write,
                           &entryOffset, sizeof(entry->VendorGroupId)); // INT16U
            copyListMember(write ? dest : (uint8_t *) &entry->GroupKeySetIndex, write ? (uint8_t *) &entry->GroupKeySetIndex : src,
                           write, &entryOffset, sizeof(entry->GroupKeySetIndex)); // INT16U
            break;
        }
        case 0x0001: // group keys
        {
            entryLength = 29;
            if (((index - 1) * entryLength) > (am->size - entryLength))
            {
                ChipLogError(Zcl, "Index %l is invalid.", index);
                return 0;
            }
            entryOffset = static_cast<uint16_t>(entryOffset + ((index - 1) * entryLength));
            // Struct _GroupKey
            _GroupKey * entry = reinterpret_cast<_GroupKey *>(write ? src : dest);
            copyListMember(write ? dest : (uint8_t *) &entry->VendorId, write ? (uint8_t *) &entry->VendorId : src, write,
                           &entryOffset, sizeof(entry->VendorId)); // INT16U
            copyListMember(write ? dest : (uint8_t *) &entry->GroupKeyIndex, write ? (uint8_t *) &entry->GroupKeyIndex : src, write,
                           &entryOffset, sizeof(entry->GroupKeyIndex)); // INT16U
            copyListMember(write ? dest : (uint8_t *) &entry->GroupKeyRoot, write ? (uint8_t *) &entry->GroupKeyRoot : src, write,
                           &entryOffset, 16); // OCTET_STRING
            copyListMember(write ? dest : (uint8_t *) &entry->GroupKeyEpochStartTime,
                           write ? (uint8_t *) &entry->GroupKeyEpochStartTime : src, write, &entryOffset,
                           sizeof(entry->GroupKeyEpochStartTime)); // INT64U
            copyListMember(write ? dest : (uint8_t *) &entry->GroupKeySecurityPolicy,
                           write ? (uint8_t *) &entry->GroupKeySecurityPolicy : src, write, &entryOffset,
                           sizeof(entry->GroupKeySecurityPolicy)); // GroupKeySecurityPolicy
            break;
        }
        }
        break;
    }
    case 0x003E: // Operational Credentials Cluster
    {
        uint16_t entryOffset = kSizeLengthInBytes;
        switch (am->attributeId)
        {
        case 0x0001: // fabrics list
        {
            entryLength = 18;
            if (((index - 1) * entryLength) > (am->size - entryLength))
            {
                ChipLogError(Zcl, "Index %l is invalid.", index);
                return 0;
            }
            entryOffset = static_cast<uint16_t>(entryOffset + ((index - 1) * entryLength));
            // Struct _FabricDescriptor
            _FabricDescriptor * entry = reinterpret_cast<_FabricDescriptor *>(write ? src : dest);
            copyListMember(write ? dest : (uint8_t *) &entry->FabricId, write ? (uint8_t *) &entry->FabricId : src, write,
                           &entryOffset, sizeof(entry->FabricId)); // FABRIC_ID
            copyListMember(write ? dest : (uint8_t *) &entry->VendorId, write ? (uint8_t *) &entry->VendorId : src, write,
                           &entryOffset, sizeof(entry->VendorId)); // INT16U
            copyListMember(write ? dest : (uint8_t *) &entry->NodeId, write ? (uint8_t *) &entry->NodeId : src, write, &entryOffset,
                           sizeof(entry->NodeId)); // NODE_ID
            break;
        }
        }
        break;
    }
    }

    return entryLength;
}

// A list is a collection of entries of the same data type. The data type may be any defined data type.
uint16_t emberAfAttributeValueListSize(ClusterId clusterId, AttributeId attributeId, const uint8_t * buffer)
{
    // The first 2 bytes specify the number of entries. A value of 0xFFFF means the list in invalid
    // and data is undefined.
    uint16_t entryCount = emberAfGetInt16u(buffer, 0, kSizeLengthInBytes);
    if (entryCount == 0xFFFF)
    {
        return 0;
    }

    uint16_t entryLength = 0;
    switch (clusterId)
    {
    case 0x001D: // Descriptor Cluster
        switch (attributeId)
        {
        case 0x0000: // device list
            // Struct _DeviceType
            entryLength = 6;
            break;
        case 0x0001: // server list
            // chip::ClusterId
            entryLength = 2;
            break;
        case 0x0002: // client list
            // chip::ClusterId
            entryLength = 2;
            break;
        case 0x0003: // parts list
            // chip::EndpointId
            entryLength = 1;
            break;
        }
        break;
    case 0xF004: // Group Key Management Cluster
        switch (attributeId)
        {
        case 0x0000: // groups
            // Struct _GroupState
            entryLength = 6;
            break;
        case 0x0001: // group keys
            // Struct _GroupKey
            entryLength = 29;
            break;
        }
        break;
    case 0x003E: // Operational Credentials Cluster
        switch (attributeId)
        {
        case 0x0001: // fabrics list
            // Struct _FabricDescriptor
            entryLength = 18;
            break;
        }
        break;
    }

    uint32_t totalSize = kSizeLengthInBytes + (entryCount * entryLength);
    if (!chip::CanCastTo<uint16_t>(totalSize))
    {
        ChipLogError(Zcl, "Cluster 0x%04x: Size of attribute 0x%02x is too large.", clusterId, attributeId);
        return 0;
    }

    return static_cast<uint16_t>(totalSize);
}
