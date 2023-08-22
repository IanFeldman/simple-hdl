#include <SDL2/SDL.h>
#include "clock.hpp"

Clock::Clock(Simulation *t_sim)
    :Module("CLOCK", "built-in")
{
    m_sim = t_sim;
    addOutput("Z");
    m_is_built_in = true;
}

int Clock::evaluate() {
    m_outputs["Z"] = m_sim->getClock();
    return 0;
}
