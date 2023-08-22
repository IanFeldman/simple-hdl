#include "nand.hpp"

Nand::Nand()
:Module("NAND", "built-in")
{
    addInput("A");
    addInput("B");
    addOutput("Z");
    m_is_built_in = true;
}

int Nand::evaluate() {
    m_outputs["Z"] = !(m_inputs["A"] && m_inputs["B"]);
    return 0;
}
