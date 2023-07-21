#include "simulation.hpp"

#define ENTRY "top"
#define EXT ".module"
#define INPUT "input"
#define OUTPUT "output" 
#define LOGIC "logic"
#define MODULE "module"

Simulation::Simulation(std::string t_directory) {
    m_directory = t_directory;
}

void Simulation::initialize() {
    std::string entry_point = m_directory + "/" + ENTRY + EXT;
    parseFile(entry_point, "top");
}

Module* Simulation::parseFile(std::string t_filename, std::string t_module_name) {
    // filestream variable file
    std::fstream file;
    std::string word, t, q;

    // opening file
    file.open(t_filename.c_str());
 
    // error occurred while opening the file.
    if (!file.is_open()) {
        std::cerr << "Error opening file:" << t_filename << std::endl;
        exit(EXIT_FAILURE);
    }

    // create module
    Module *module = new Module(t_module_name);
    addModule(module);

    // extracting words from the file
    while (file >> word)
    {
        if (word == INPUT) {
            std::string input_name;
            file >> input_name;
            module->addInput(input_name);
        }
        else if (word == OUTPUT) {
            std::string output_name;
            module->addOutput(output_name);
        }
        else if (word == LOGIC) {
            std::string logic_name, logic_value;
            file >> logic_name;
            file >> logic_value;
            int value = 0;
            if (logic_value != "0") {
                value = 1;
            }
            module->addLogic(logic_name, value);
        }
        else if (word == MODULE) {
            std::string module_name, module_filename, parameter_name, parameter_value;
            // create new module
            file >> module_name;
            file >> module_filename;
            module_filename += EXT;
            Module *new_module = parseFile(module_filename, module_name);
            // associate with current 
            file >> parameter_name;
            file >> parameter_value;
        }
    }

    file.close();

    return module;
}
