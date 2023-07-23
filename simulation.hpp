#pragma once
#include <bits/stdc++.h>
#include <vector>
#include "module.hpp"

class Simulation {
public:
    Simulation(std::string t_directory);
    void initialize();
    Module *parseFile(std::string t_file_name, std::string t_module_name);
    void addModule(Module *t_module) { m_modules.push_back(t_module); }
    std::string createFilePath(std::string t_module_name);
    void debug();
    void shutdown();

private:
    std::string m_directory;
    std::vector<Module*> m_modules;
    bool m_running;
    int m_clock;
};
