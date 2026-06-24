#include "block.h"
/*
    Search pid | port_type: out/in | port_num
*/
PortConnection parse_port(const std::string &str)
{
    PortConnection port_connection;
    size_t hash_index = str.find('#');
    size_t colon_index = str.find(':');
    if (hash_index != std::string::npos && colon_index != std::string::npos)
    {
        port_connection.sid = str.substr(0, hash_index);
        port_connection.port_type = str.substr(hash_index + 1, colon_index - (hash_index + 1));
        port_connection.port_num = std::stoi(str.substr(colon_index + 1));
    }
    return port_connection;
}

/*
    Give name for block
*/
std::string get_port_variable(const PortConnection &pc, const std::map<std::string, Block> &blocks)
{
    auto iter = blocks.find(pc.sid);
    if (iter != blocks.end())
    {
        return "nwocg." + sanitize_name(iter->second.name);
    }
    return "ERROR";
}