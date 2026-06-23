#include <string>
#include <map>

#include "DSL_lib/block_structure/block.h"

std::string build_sum_expression(
    const Block &block,
    const std::map<int, PortConnection> &inputs,
    const std::map<std::string, Block> &blocks) {};

std::string build_logic_expression(
    const Block &block,
    const std::map<int, PortConnection> &inputs,
    const std::map<std::string, Block> &blocks) {};

std::string build_relational_expression(
    const Block &block,
    const std::map<int, PortConnection> &inputs,
    const std::map<std::string, Block> &blocks) {};