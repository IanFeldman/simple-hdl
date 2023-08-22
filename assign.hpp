#pragma once
#include "module.hpp"

class Assign : public Module {
public:
    Assign();
    int evaluate() override;
};
