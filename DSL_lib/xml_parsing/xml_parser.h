#include <vector>
#include <string>
#include <map>

#include "tinyxml2.h"
#include "DSL_lib/block_structure/block.h"

void find_dsts(tinyxml2::XMLElement *node, std::vector<std::string> &dsts) {};

void parse_blocks(
    tinyxml2::XMLElement *root,
    std::map<std::string, Block> &blocks,
    std::vector<std::string> &xml_block_order) {};

void parse_lines(
    tinyxml2::XMLElement *root,
    std::map<std::string, std::map<int, PortConnection>> &block_inputs) {};
