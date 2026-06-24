#pragma once
#include <string>
#include <map>

struct PortConnection
{
    std::string sid;
    std::string port_type;
    int port_num = 0;
};

/*
    Block struct: block + operations (arithmetics & logic: and, or, xor, not; and relations)
*/
struct Block
{
    std::string sid;
    std::string type;
    std::string name;
    double gain = 1.0;
    std::string inputs_pattern = "++";
    std::string logic_op = "";      // Для Logic (AND, OR, XOR, NOT)
    std::string relational_op = ""; // Для RelationalOperator (==, !=, <, etc.)
};

struct ExtPort
{
    std::string name;
    std::string addr;
    int type;
};

// Search pid | port_type: out/in | port_num
PortConnection parse_port(const std::string &str);

// Give name for block
std::string get_port_variable(const PortConnection &pc, const std::map<std::string, Block> &blocks);

std::string sanitize_name(const std::string &name);
std::string format_double(double val);
bool is_combinational(const std::string &type);
