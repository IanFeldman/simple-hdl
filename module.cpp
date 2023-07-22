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
