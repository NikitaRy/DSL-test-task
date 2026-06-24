#include "blocks_streaming.h"
#include "DSL_lib/expressions_building/expressions_building.h"

void write_struct_definition(
    std::ostream &outStream,
    const std::map<std::string, Block> &blocks,
    const std::vector<std::string> &xml_block_order)
{
    outStream << "static struct\n{\n";
    for (const auto &sid : xml_block_order)
    {
        const auto &block = blocks.at(sid);
        if (block.type == "Inport")
        {
            outStream << "  double " << sanitize_name(block.name) << ";\n";
        }
    }
    for (const auto &sid : xml_block_order)
    {
        const auto &block = blocks.at(sid);
        if (is_combinational(block.type) || block.type == "UnitDelay")
        {
            outStream << "  double " << sanitize_name(block.name) << ";\n";
        }
    }
    outStream << "} nwocg;\n\n";
}

void write_init_function(
    std::ostream &outStream,
    const std::map<std::string, Block> &blocks,
    const std::vector<std::string> &xml_block_order)
{
    outStream << "void nwocg_generated_init()\n{\n";
    for (const auto &sid : xml_block_order)
    {
        const auto &block = blocks.at(sid);
        if (block.type == "UnitDelay")
        {
            outStream << "  nwocg." << sanitize_name(block.name) << " = 0;\n";
        }
    }
    outStream << "}\n\n";
}

void write_step_function(
    std::ostream &outStream,
    const std::map<std::string, Block> &blocks,
    const std::vector<std::string> &xml_block_order,
    const std::map<std::string, std::map<int, PortConnection>> &block_inputs,
    const std::vector<std::string> &execution_order)
{
    outStream << "void nwocg_generated_step()\n{\n";
    for (const std::string &sid : execution_order)
    {
        const auto &block = blocks.at(sid);
        outStream << "  nwocg." << sanitize_name(block.name) << " = ";

        if (block.type == "Gain" && block_inputs.count(sid) && block_inputs.at(sid).count(1))
        {
            std::string input_var = get_port_variable(block_inputs.at(sid).at(1), blocks);
            outStream << input_var << " * " << format_double(block.gain) << ";\n";
        }
        else if (block.type == "Sum" && block_inputs.count(sid))
        {
            outStream << build_sum_expression(block, block_inputs.at(sid), blocks) << ";\n";
        }
        else if (block.type == "Logic" && block_inputs.count(sid))
        {
            outStream << build_logic_expression(block, block_inputs.at(sid), blocks) << ";\n";
        }
        else if (block.type == "RelationalOperator" && block_inputs.count(sid))
        {
            outStream << build_relational_expression(block, block_inputs.at(sid), blocks) << ";\n";
        }
    }
    outStream << "\n";
    for (const auto &sid : xml_block_order)
    {
        const auto &b = blocks.at(sid);
        if (b.type == "UnitDelay")
        {
            if (block_inputs.count(sid) && block_inputs.at(sid).count(1))
            {
                std::string input_var = get_port_variable(block_inputs.at(sid).at(1), blocks);
                outStream << "  nwocg." << sanitize_name(b.name) << " = " << input_var << ";\n";
            }
        }
    }
    outStream << "}\n\n";
}

void write_external_ports(
    std::ostream &outStream,
    const std::map<std::string, Block> &blocks,
    const std::map<std::string, std::map<int, PortConnection>> &block_inputs)
{
    std::vector<ExtPort> ext_ports;
    for (const auto &[sid, block] : blocks)
    {
        if (block.type == "Inport")
        {
            ext_ports.push_back({block.name, "&nwocg." + sanitize_name(block.name), 1});
        }
        else if (block.type == "Outport")
        {
            if (block_inputs.count(sid) && block_inputs.at(sid).count(1))
            {
                std::string source_var = get_port_variable(block_inputs.at(sid).at(1), blocks);
                ext_ports.push_back({block.name, "&" + source_var, 0});
            }
        }
    }

    std::sort(ext_ports.begin(), ext_ports.end(), [](const ExtPort &a, const ExtPort &b)
              { return a.name < b.name; });

    outStream << "static const nwocg_ExtPort\n  ext_ports[] =\n{\n";
    for (const auto &external_ports : ext_ports)
    {
        outStream << "  { \"" << external_ports.name << "\", " << external_ports.addr << ", " << external_ports.type << " },\n";
    }
    outStream << "  { 0, 0, 0 },\n";
    outStream << "};\n\n";

    outStream << "const nwocg_ExtPort * const\n  nwocg_generated_ext_ports = ext_ports;\n\n";
    outStream << "const size_t\n  nwocg_generated_ext_ports_size = sizeof(ext_ports);\n";
}