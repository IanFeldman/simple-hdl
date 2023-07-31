#include "module.hpp"

Module::Module(std::string t_name, std::string t_file_name) {
    m_name = t_name;
    m_file_name = t_file_name;
}

void Module::addInput(std::string t_name) {
    m_inputs[t_name] = 0;
}

void Module::addOutput(std::string t_name) {
    m_outputs[t_name] = 0;
}

void Module::addLogic(std::string t_name, int t_value) {
    m_logics[t_name] = t_value;
}

void Module::addConnection(Connection t_connection) {
    m_connections.push_back(t_connection);
}

void Module::evaluate() {
    // iterate over connections
    for (Connection c : m_connections) {
        std::unordered_map<std::string, int> *submodule_inputs = c.module->getInputs();
        std::unordered_map<std::string, int> *submodule_outputs = c.module->getOutputs();

        // iterate over inputs and update submodule
        for (auto& it: *submodule_inputs) {
            // sub input
            std::string submodule_input = it.first;
            // super input/logic to be fed in
            std::string supermodule_parameter = c.port_map[submodule_input];
            // check if sup par is input, logic, or output
            int super_value;
            if (m_inputs.count(supermodule_parameter)) {
                super_value = m_inputs[supermodule_parameter];
            }
            else if (m_logics.count(supermodule_parameter)) {
                super_value = m_logics[supermodule_parameter];
            }
            else if (m_outputs.count(supermodule_parameter)) {
                std::cout << "(" << m_file_name << ") ";
                std::cout << "Error evaluating module '" << c.module->getName() << "': ";
                std::cout << "cannot connect supermodule output to submodule input" << std::endl;
                return;
            }
            else {
                std::cout << "(" << m_file_name << ") ";
                std::cout << "Error evaluating module '" << c.module->getName() << "': ";
                std::cout << "unconnected submodule input" << std::endl;
                return;
            }
            // set submodule input value
            (*submodule_inputs)[submodule_input] = super_value;
        }

        // evaluate submodule outputs
        c.module->evaluate();

        // iterate over outputs and update supermodule
        for (auto& it: *submodule_outputs) {
            // sub output
            std::string submodule_output = it.first;
            // super output/logic to receive sub out
            std::string supermodule_parameter = c.port_map[submodule_output];
            // check if sup par is output, logic, or input
            if (m_outputs.count(supermodule_parameter)) {
                m_outputs[supermodule_parameter] = (*submodule_outputs)[submodule_output];
            }
            else if (m_logics.count(supermodule_parameter)) {
                m_logics[supermodule_parameter] = (*submodule_outputs)[submodule_output];
            }
            else if (m_inputs.count(supermodule_parameter)) {
                std::cout << "(" << m_file_name << ") ";
                std::cout << "Error evaluating module '" << c.module->getName() << "': ";
                std::cout << "cannot connect submodule output to supermodule input" << std::endl;
                return;
            }
            else {
                std::cout << "(" << m_file_name << ") ";
                std::cout << "Error evaluating module '" << c.module->getName() << "': ";
                std::cout << "unconnected submodule output" << std::endl;
                return;
            }
        }
    }
}
