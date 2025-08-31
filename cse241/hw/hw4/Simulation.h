#ifndef SIMULATION_H
#define SIMULATION_H

#include "Constants.h"
#include "Robot.h"
#include "Humanic.h"
#include "OptimusPrime.h"
#include "RoboCop.h"
#include "Roomba.h"
#include "Bulldozer.h"
#include "Kamikaze.h"
#include <string>
#include <vector>

class Simulation {
private:
    Robot*** grid;
    std::vector<Robot*> robots;
    int robotCount;
    
    // Helper functions
    void initializeGrid();
    void displayGrid() const;
    void moveRobots();
    bool moveRobotsUntilCombat(); // New method
    void fight(Robot* attacker, Robot* victim);
    bool isGameOver() const;
    void healHumanicRobots();
    void cleanupDeadRobots();
    
public:
    Simulation();
    ~Simulation();
    
    void run();
    void createRobots();
};

#endif