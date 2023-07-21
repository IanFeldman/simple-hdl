#pragma once

#include "module.hpp"
#include <bits/stdc++.h>
#include <vector>

class Simulation {
public:
    Simulation(std::string t_directory);
    void initialize();
    Module* parseFile(std::string t_filename, std::string t_module_name);
    void addModule(Module* t_module) { m_modules.push_back(t_module); }

private:
    std::string m_directory;
    std::vector<Module*> m_modules;
};
