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

#pragma once
#define CHIP_CSG_TEST_HARNESS 1

#define CHARS_PER_BYTE (uint16_t)2
#include <map>
#include <string>
#include <stdlib.h>

const char * yaml_string_for_map(std::map<std::string, std::map<std::string, std::string>> *trace_map);
std::string stringForDataBuffer(uint8_t *start, uint16_t data_length);

extern std::string PBKDFParamRequest_str_key;
extern std::string randomFromInitiator_str_key;
