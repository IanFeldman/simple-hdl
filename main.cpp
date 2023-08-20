#include "simulation.hpp"
#include <iostream>
 
int main(int argc, char *argv[])
{
    // check arguments
    if (argc != 3) {
        std::cout << "Usage error" << std::endl;
        std::cout << "./simple-hdl [path to modules directory] [clock speed]" << std::endl;
        return EXIT_FAILURE;
    }
    char *directory = argv[1];
    int clock_speed = atoi(argv[2]);

    Simulation sim = Simulation(directory, clock_speed);
    sim.initialize();
   
    return EXIT_SUCCESS;
}
