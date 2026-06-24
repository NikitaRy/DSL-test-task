#pragma once
#include <sstream>
#include <map>
#include <vector>

#include "DSL_lib/block_structure/block.h"

void write_struct_definition(
    std::ostream &outStream,
    const std::map<std::string, Block> &blocks,
    const std::vector<std::string> &xml_block_order);

void write_init_function(
    std::ostream &outStream,
    const std::map<std::string, Block> &blocks,
    const std::vector<std::string> &xml_block_order);

void write_step_function(
    std::ostream &outStream,
    const std::map<std::string, Block> &blocks,
    const std::vector<std::string> &xml_block_order,
    const std::map<std::string, std::map<int, PortConnection>> &block_inputs,
    const std::vector<std::string> &execution_order);

void write_external_ports(
    std::ostream &outStream,
    const std::map<std::string, Block> &blocks,
    const std::map<std::string, std::map<int, PortConnection>> &block_inputs);