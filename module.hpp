#include <bits/stdc++.h>
#include <unordered_map>

class Module {
public:
    Module(std::string t_name);
    void addInput(std::string t_name);
    void addOutput(std::string t_name);
    void addLogic(std::string t_name, int t_value);

private:
    std::string m_name;
    std::unordered_map<std::string, int> m_inputs, m_outputs, m_logics;
};
