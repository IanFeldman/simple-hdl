#pragma once
#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>

class Module {
public:
    struct Connection {
        // the connected submodule
        Module *module;
        // mapping of ports
        // key: submodule port name, value: supermodule port name
        std::unordered_map<std::string, std::string> port_map;
    };
    Module(std::string t_name, std::string t_file_name);
    void addInput(std::string t_name);
    void addOutput(std::string t_name);
    void addLogic(std::string t_name, int t_value);
    void addConnection(Connection t_connection) { m_connections.push_back(t_connection); }
    // getters/setters
    std::string getName() { return m_name; }
    std::string getFileName() { return m_file_name; }
    std::unordered_map<std::string, int> getInputs() { return m_inputs; }
    std::unordered_map<std::string, int> getOutputs() { return m_outputs; }
    std::unordered_map<std::string, int> getLogics() { return m_logics; }
    std::vector<Connection> getConnections() { return m_connections; }

private:
    std::string m_name, m_file_name;
    std::unordered_map<std::string, int> m_inputs, m_outputs, m_logics;
    std::vector<Connection> m_connections;
};
