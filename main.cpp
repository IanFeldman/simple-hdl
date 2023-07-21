#include "simulation.hpp"
 
int main(int argc, char *argv[])
{
    // check arguments
    /*
    if (argc != 2) {
        std::cerr << "Incorrect usage" << std::endl;
        return EXIT_FAILURE;
    }
    char *directory = argv[1];
    */

    Simulation sim = Simulation("modules");
    sim.initialize();
   
    return EXIT_SUCCESS;
}
