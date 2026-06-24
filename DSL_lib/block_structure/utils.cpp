#include <string>
#include <sstream>
#include "block.h"

/*
    Delete spaces from names
*/
std::string sanitize_name(const std::string &name)
{
    std::string res;
    for (char ch : name)
    {
        if (ch != ' ')
            res += ch;
    }
    return res;
}

std::string format_double(double val)
{
    std::ostringstream stream;
    stream << val;
    return stream.str();
}

/*
    We need this function to make topological sorting easier.
*/
bool is_combinational(const std::string &type)
{
    return type == "Sum" || type == "Gain" || type == "Logic" || type == "RelationalOperator";
}
