#pragma once
#include "module.hpp"

class Nand : public Module {
public:
    Nand();
    int evaluate() override;
};
