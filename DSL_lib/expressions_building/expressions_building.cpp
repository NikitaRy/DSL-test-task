#include "expressions_building.h"

std::string build_sum_expression(
    const Block &block,
    const std::map<int, PortConnection> &inputs,
    const std::map<std::string, Block> &blocks)
{
    std::string expr = "";
    int num_inputs = inputs.size();
    for (int i = 1; i <= num_inputs; ++i)
    {
        if (inputs.count(i))
        {
            char sign = '+';
            if (i - 1 < block.inputs_pattern.size())
            {
                sign = block.inputs_pattern[i - 1];
            }
            std::string var = get_port_variable(inputs.at(i), blocks);
            if (i == 1)
            {
                expr += (sign == '-') ? "-" + var : var;
            }
            else
            {
                expr += (sign == '-') ? " - " : " + ";
                expr += var;
            }
        }
    }
    return expr;
}

std::string build_logic_expression(
    const Block &block,
    const std::map<int, PortConnection> &inputs,
    const std::map<std::string, Block> &blocks)
{
    if (block.logic_op == "NOT")
    {
        if (inputs.count(1))
        {
            return "!(" + get_port_variable(inputs.at(1), blocks) + ")";
        }
        return "0";
    }

    std::string op = " && ";
    if (block.logic_op == "OR")
        op = " || ";
    else if (block.logic_op == "XOR")
        op = " ^ ";

    std::string expr = "";
    int num_inputs = inputs.size();
    bool first = true;
    for (int i = 1; i <= num_inputs; ++i)
    {
        if (inputs.count(i))
        {
            std::string var = get_port_variable(inputs.at(i), blocks);
            if (first)
            {
                expr += var;
                first = false;
            }
            else
            {
                expr += op + var;
            }
        }
    }
    return expr;
}

std::string build_relational_expression(
    const Block &block,
    const std::map<int, PortConnection> &inputs,
    const std::map<std::string, Block> &blocks)
{
    if (inputs.count(1) && inputs.count(2))
    {
        std::string v1 = get_port_variable(inputs.at(1), blocks);
        std::string v2 = get_port_variable(inputs.at(2), blocks);

        std::string sym = " == ";
        std::string op = block.relational_op;
        if (op == "!=" || op == "~=")
            sym = " != ";
        else if (op == "<" || op == "&lt;")
            sym = " < ";
        else if (op == "<=" || op == "&lt;=")
            sym = " <= ";
        else if (op == ">" || op == "&gt;")
            sym = " > ";
        else if (op == ">=" || op == "&gt;=")
            sym = " >= ";

        return "(" + v1 + sym + v2 + ")";
    }
    return "0";
}