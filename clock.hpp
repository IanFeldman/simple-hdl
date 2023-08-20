#pragma once
#include "module.hpp"
#include "simulation.hpp"

class Clock : public Module {
public:
    Clock(Simulation *t_sim);
    void evaluate() override;

private:
    Simulation *m_sim;
};
