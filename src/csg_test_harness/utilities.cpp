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

#include "constants.h"
#include <string.h>
#include <iostream>
// Request Parameter Keys
std::string PBKDFParamRequest_str_key ("PBKDFParamRequest");
std::string messageFromInitiator_str_key ("MessageFromInitiator");

// Response Parameter Keys
std::string messageFromResponder_str_key ("MessageFromResponder");
std::string PBKDFParamResponse_str_key ("PBKDFParamResponse");

const char * yaml_string_for_map(std::map<std::string, std::map<std::string, std::string>> *trace_map)
{
    std::string result_yaml_str = "";
    for (auto& x: *trace_map) {
        // for each message
        result_yaml_str += x.first;
        result_yaml_str += ":\n";
        for (auto& y: x.second) {
            // for each message item
            result_yaml_str += "  "; // indent 2 spaces for nested hash
            result_yaml_str += y.first;
            result_yaml_str += ": ";
            result_yaml_str += y.second;
            std::cout << "Key: " << y.first << " Value: " << y.second << std::endl;
            result_yaml_str += "\n";
        }
    }

    char * response = new char [result_yaml_str.length()+1];
    strcpy(response, result_yaml_str.c_str());
    return response;
}

std::string stringForDataBuffer(const uint8_t *start, uint16_t data_length)
{
    uint16_t total_length = (uint16_t)((data_length * CHARS_PER_BYTE) + 1);
    char * data_string_ptr = (char *)malloc(total_length * sizeof(char));
    std::string data_string;
    for (uint16_t i=0; i < data_length; i++) {
        sprintf(data_string_ptr+i*2, "%02x", start[i]);
    }
    data_string_ptr[data_length*2] = '\0';
    data_string = std::string(data_string_ptr);
    return data_string;
}
