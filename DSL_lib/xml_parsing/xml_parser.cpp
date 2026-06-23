#include <vector>
#include <string>
#include <map>

#include "tinyxml2.h"
#include "xml_parser.h"

void find_dsts(tinyxml2::XMLElement *node, std::vector<std::string> &dsts)
{
    for (tinyxml2::XMLElement *child = node->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
    {
        std::string name = child->Value();
        if (name == "P")
        {
            const char *p_name = child->Attribute("Name");
            if (p_name && std::string(p_name) == "Dst" && child->GetText())
            {
                dsts.push_back(child->GetText());
            }
        }
        else if (name == "Branch")
        {
            find_dsts(child, dsts);
        }
    }
}

void parse_blocks(tinyxml2::XMLElement *root, std::map<std::string, Block> &blocks, std::vector<std::string> &xml_block_order)
{
    for (tinyxml2::XMLElement *xml_block = root->FirstChildElement("Block"); xml_block != nullptr; xml_block = xml_block->NextSiblingElement("Block"))
    {
        Block block;
        block.sid = xml_block->Attribute("SID");
        block.type = xml_block->Attribute("BlockType");
        block.name = xml_block->Attribute("Name");

        for (tinyxml2::XMLElement *child = xml_block->FirstChildElement("P"); child != nullptr; child = child->NextSiblingElement("P"))
        {
            const char *p_name = child->Attribute("Name");
            if (p_name)
            {
                std::string name_str(p_name);
                if (name_str == "Gain" && child->GetText())
                {
                    block.gain = std::stod(child->GetText());
                }
                else if (name_str == "Inputs" && child->GetText())
                {
                    block.inputs_pattern = child->GetText();
                }
                else if (name_str == "Operator" && child->GetText())
                {
                    if (block.type == "Logic")
                        block.logic_op = child->GetText();
                    else if (block.type == "RelationalOperator")
                        block.relational_op = child->GetText();
                }
            }
        }
        blocks[block.sid] = block;
        xml_block_order.push_back(block.sid);
    }
}

void parse_lines(tinyxml2::XMLElement *root, std::map<std::string, std::map<int, PortConnection>> &block_inputs)
{
    for (tinyxml2::XMLElement *line = root->FirstChildElement("Line"); line != nullptr; line = line->NextSiblingElement("Line"))
    {
        const char *src_str = nullptr;
        for (tinyxml2::XMLElement *childElement = line->FirstChildElement("P"); childElement != nullptr; childElement = childElement->NextSiblingElement("P"))
        {
            const char *childElement_name = childElement->Attribute("Name");
            if (childElement_name && std::string(childElement_name) == "Src")
            {
                src_str = childElement->GetText();
            }
        }
        if (!src_str)
            continue;
        PortConnection src_pc = parse_port(src_str);

        std::vector<std::string> dst_strs;
        find_dsts(line, dst_strs);

        for (const auto &dst_str : dst_strs)
        {
            PortConnection dst_pc = parse_port(dst_str);
            block_inputs[dst_pc.sid][dst_pc.port_num] = src_pc;
        }
    }
}