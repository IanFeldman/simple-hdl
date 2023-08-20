#pragma once
#include <unordered_map>
#include "module.hpp"

class Keyboard : public Module {
public:
    Keyboard();
    void evaluate() override;
    static std::unordered_map<std::string, int> valid_keys;
};
