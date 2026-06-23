#include <vector>
#include <map>
#include <queue>

#include "DSL_lib/block_structure/block.h"
#include "DSL_lib/block_structure/utils.cpp"

std::vector<std::string> perform_topological_sort(
    const std::map<std::string, Block> &blocks,
    const std::map<std::string, std::map<int, PortConnection>> &block_inputs)
{
    std::map<std::string, int> input_degree;
    std::map<std::string, std::vector<std::string>> adj;

    for (auto const &[sid, block] : blocks)
    {
        if (is_combinational(block.type))
        {
            input_degree[sid] = 0;
            adj[sid] = {};
        }
    }

    for (auto const &[dest_sid, block] : blocks)
    {
        if (!is_combinational(block.type))
            continue;
        if (block_inputs.count(dest_sid))
        {
            for (auto const &[port_num, src_pc] : block_inputs.at(dest_sid))
            {
                std::string src_sid = src_pc.sid;
                if (blocks.count(src_sid))
                {
                    std::string src_type = blocks.at(src_sid).type;
                    if (is_combinational(src_type))
                    {
                        adj[src_sid].push_back(dest_sid);
                        input_degree[dest_sid]++;
                    }
                }
            }
        }
    }

    std::queue<std::string> q;
    for (auto const &[sid, deg] : input_degree)
    {
        if (deg == 0)
            q.push(sid);
    }

    std::vector<std::string> execution_order;
    while (!q.empty())
    {
        std::string u = q.front();
        q.pop();
        execution_order.push_back(u);
        for (std::string v : adj[u])
        {
            input_degree[v]--;
            if (input_degree[v] == 0)
                q.push(v);
        }
    }
    return execution_order;
}