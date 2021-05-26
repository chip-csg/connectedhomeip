#include "constants.h"
#include <string.h>
std::string randomFromInitiator_str_key ("RandomFromInitiator");
std::string PBKDFParamRequest_str_key ("PBKDFParamRequest");

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
            result_yaml_str += "\n";
        }
    }

    char * response = new char [result_yaml_str.length()+1];
    strcpy(response, result_yaml_str.c_str());
    return response;
}