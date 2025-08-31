#include "Simulation.h"
#include <cstdlib>
#include <ctime>

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Create and run the simulation
    Simulation sim;
    sim.run();
    
    return 0;
}