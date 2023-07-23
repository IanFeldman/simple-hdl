#include "simulation.hpp"
#include "nand.hpp"

// syntax
#define ENTRY "top"
#define EXT ".module"
#define INPUT "input"
#define OUTPUT "output" 
#define LOGIC "logic"
#define MODULE "module"
#define ENDMODULE "endmodule"
#define NAND "nand"
#define COMMENT "#"

Simulation::Simulation(std::string t_directory) {
    m_directory = t_directory;
}

void Simulation::initialize() {
    Module *top_module = parseFile(createFilePath(ENTRY), "top");
    top_module->evaluate();
    debug();
    shutdown();
}

Module *Simulation::parseFile(std::string t_file_name, std::string t_module_name) {
    // filestream variable file
    std::fstream file;
    std::string word;

    // opening file
    file.open(t_file_name.c_str());
 
    // error occurred while opening the file.
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << t_file_name << std::endl;
        exit(EXIT_FAILURE);
    }

    // create module
    Module *module = new Module(t_module_name, t_file_name);
    addModule(module);

    // extracting words from the file
    while (file >> word)
    {
        if (word == COMMENT) {
            file >> word;
            while (word != COMMENT) {
                file >> word;
            }
        }
        else if (word == INPUT) {
            std::string input_name;
            file >> input_name;
            module->addInput(input_name);
        }
        else if (word == OUTPUT) {
            std::string output_name;
            file >> output_name;
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
            std::string module_name, module_filename, port_name, port_value;
            // create new module
            file >> module_name;
            file >> module_filename;
            Module *new_module = parseFile(createFilePath(module_filename), module_name);
            // create connection
            Module::Connection connection;
            connection.module = new_module;
            // create map
            std::unordered_map<std::string, std::string> port_map;
            file >> port_name;
            while (port_name != ENDMODULE) {
                file >> port_value;
                port_map[port_name] = port_value; 
                file >> port_name;
            }
            connection.port_map = port_map;
            // add connection
            module->addConnection(connection);
        }
        else if (word == NAND) {
            Nand *nand = new Nand();
            addModule(nand);
            // create connection
            Module::Connection connection;
            connection.module = nand;
            // create map
            std::unordered_map<std::string, std::string> port_map;
            file >> port_map["A"]; 
            file >> port_map["B"];
            file >> port_map["Z"];
            connection.port_map = port_map;
            // add connection
            module->addConnection(connection);
        }
    }

    file.close();
    return module;
}

std::string Simulation::createFilePath(std::string t_module_name) {
    return m_directory + "/" + t_module_name + EXT;
}

void Simulation::debug() {
    for (Module *m : m_modules) {
        std::cout << m->getName() << "(" << m->getFileName() << ")" << std::endl;

        std::cout << "  INPUTS" << std::endl;
        for (auto& it: *m->getInputs()) {
            std::cout << "    " << it.first << " : " << (*m->getInputs())[it.first] << std::endl;
        }

        std::cout << "  OUTPUTS" << std::endl;
        for (auto& it: *m->getOutputs()) {
            std::cout << "    " << it.first << " : " << (*m->getOutputs())[it.first] << std::endl;
        }

        std::cout << "  LOGICS" << std::endl;
        for (auto& it: *m->getLogics()) {
            std::cout << "    " << it.first << " : " << (*m->getLogics())[it.first] << std::endl;
        }

        std::cout << "  CONNECTIONS" << std::endl;
        for (Module::Connection c : m->getConnections()) {
            // name
            std::cout << "    " << c.module->getName() << "(" << c.module->getFileName() << ")" << std::endl;
            // iterate over ports
            for (auto& it: c.port_map) {
                std::cout << "      " << it.first << " <-> " << c.port_map[it.first] << std::endl;
            }
        }
        std::cout << std::endl;
    }
}

void Simulation::shutdown() {
    for (Module *m : m_modules) {
        delete m;
    }
}
