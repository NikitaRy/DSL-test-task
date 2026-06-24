#include "DSL_lib/expressions_building/expressions_building.h"
#include "DSL_lib/code_generation/code_generation.h"
#include "DSL_lib/xml_parsing/xml_parser.h"

int main()
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError eResult = doc.LoadFile("example_model.xml");
    if (eResult != tinyxml2::XML_SUCCESS)
    {
        std::cerr << "Error: Can't upload .xml with ID: " << eResult << std::endl;
        return 1;
    }

    tinyxml2::XMLElement *root = doc.FirstChildElement("System");
    if (root == nullptr)
    {
        std::cerr << "<System> not found." << std::endl;
        return 1;
    }

    std::map<std::string, Block> blocks;
    std::vector<std::string> xml_block_order;
    std::map<std::string, std::map<int, PortConnection>> block_inputs;

    parse_blocks(root, blocks, xml_block_order);
    parse_lines(root, block_inputs);

    std::vector<std::string> execution_order = perform_topological_sort(blocks, block_inputs);

    generate_c_code("nwocg_generated.c", blocks, xml_block_order, block_inputs, execution_order);

    return 0;
}