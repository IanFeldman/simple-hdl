#pragma once
#include <unordered_map>
#include <unordered_set>
#include "module.hpp"

class Keyboard : public Module {
public:
    Keyboard();
    int evaluate() override;
    static std::unordered_map<std::string, int> valid_keys;
    void toggleEnable(std::string t_key) { m_toggle_enabled[t_key] = true; }

private:
    // press and hold enabled by default
    // outputs in here are set to toggle-enable, and the value is whether they can be toggled now
    std::unordered_map<std::string, bool> m_toggle_enabled;
};
