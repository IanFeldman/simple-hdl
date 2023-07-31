#pragma once
#include <unordered_set>
#include "module.hpp"

class Keyboard : public Module {
public:
    Keyboard();
    void evaluate() override;
    static const std::unordered_set<std::string> valid_keys;
};
