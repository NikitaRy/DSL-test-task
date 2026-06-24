#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include "DSL_lib/blocks_streaming/blocks_streaming.h"

void generate_c_code(
    const std::string &output_filename,
    const std::map<std::string, Block> &blocks,
    const std::vector<std::string> &xml_block_order,
    const std::map<std::string, std::map<int, PortConnection>> &block_inputs,
    const std::vector<std::string> &execution_order);