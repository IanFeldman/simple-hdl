#include "nand.hpp"

Nand::Nand()
:Module("NAND", "built-in")
{
    addInput("A");
    addInput("B");
    addOutput("Z");
}

void Nand::evaluate() {
    m_outputs["Z"] = !(m_inputs["A"] && m_inputs["B"]);
}
