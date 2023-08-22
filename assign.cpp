#include <SDL2/SDL.h>
#include "assign.hpp"

Assign::Assign()
    :Module("ASSIGN", "built-in")
{
    addInput("A");
    addOutput("Z");
    m_is_built_in = true;
}

int Assign::evaluate() {
    m_outputs["Z"] = m_inputs["A"];
    return 0;
}
