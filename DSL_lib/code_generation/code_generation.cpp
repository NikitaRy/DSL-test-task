#include "code_generation.h"

void generate_c_code(
    const std::string &output_filename,
    const std::map<std::string, Block> &blocks,
    const std::vector<std::string> &xml_block_order,
    const std::map<std::string, std::map<int, PortConnection>> &block_inputs,
    const std::vector<std::string> &execution_order)
{
    std::ofstream outStream(output_filename);
    if (!outStream.is_open())
    {
        std::cerr << "Can't open file for writting: " << output_filename << std::endl;
        return;
    }

    outStream << "#include \"nwocg_run.h\"\n";
    outStream << "#include <math.h>\n\n";

    write_struct_definition(outStream, blocks, xml_block_order);
    write_init_function(outStream, blocks, xml_block_order);
    write_step_function(outStream, blocks, xml_block_order, block_inputs, execution_order);
    write_external_ports(outStream, blocks, block_inputs);

    outStream.close();
    std::cout << "Successfully saved: " << output_filename << std::endl;
}