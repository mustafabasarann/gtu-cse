#include "Simulation.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

Simulation::Simulation() : robotCount(0) {
    // Create the grid
    grid = new Robot**[GRID_SIZE];
    for (int i = 0; i < GRID_SIZE; i++) {
        grid[i] = new Robot*[GRID_SIZE];
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = nullptr;
        }
    }
}

Simulation::~Simulation() {
    // Clean up the grid
    for (int i = 0; i < GRID_SIZE; i++) {
        delete[] grid[i];
    }
    delete[] grid;
    
    // Clean up the robots
    for (auto robot : robots) {
        delete robot;
    }
}

void Simulation::initializeGrid() {
    // Clear the grid
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = nullptr;
        }
    }
}

void Simulation::displayGrid() const {
    std::cout << "Current Grid:" << std::endl;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == nullptr) {
                std::cout << ". ";
            } else {
                // First letter of robot type
                std::cout << grid[i][j]->getType()[0] << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Simulation::createRobots() {
    // Create robots of each type
    for (int i = 0; i < INITIAL_COUNT_EACH_TYPE; i++) {
        std::string name;
        Robot* robot;
        
        // OptimusPrime
        name = "optimusprime_" + std::to_string(i);
        robot = new OptimusPrime(name);
        robots.push_back(robot);
        
        // RoboCop
        name = "robocop_" + std::to_string(i);
        robot = new RoboCop(name);
        robots.push_back(robot);
        
        // Roomba
        name = "roomba_" + std::to_string(i);
        robot = new Roomba(name);
        robots.push_back(robot);
        
        // Bulldozer
        name = "bulldozer_" + std::to_string(i);
        robot = new Bulldozer(name);
        robots.push_back(robot);
        
        // Kamikaze
        name = "kamikaze_" + std::to_string(i);
        robot = new Kamikaze(name);
        robots.push_back(robot);
    }
    
    robotCount = robots.size();
    
    // Place robots randomly in the grid
    for (auto robot : robots) {
        int x, y;
        do {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;
        } while (grid[x][y] != nullptr);
        
        grid[x][y] = robot;
    }
}

void Simulation::moveRobots() {
    // Reset moved flags
    for (auto robot : robots) {
        if (robot != nullptr) {
            robot->setMoved(false);
        }
    }
    
    // Move each robot
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != nullptr && !grid[i][j]->hasMoved()) {
                Robot* robot = grid[i][j];
                robot->setMoved(true);
                
                // Try to move
                int dir = rand() % 4; // 0: up, 1: right, 2: down, 3: left
                int newX = i, newY = j;
                
                switch (dir) {
                    case 0: newX--; break; // Up
                    case 1: newY++; break; // Right
                    case 2: newX++; break; // Down
                    case 3: newY--; break; // Left
                }
                
                // Check if new position is valid
                if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE) {
                    if (grid[newX][newY] == nullptr) {
                        // Move to empty cell
                        grid[newX][newY] = robot;
                        grid[i][j] = nullptr;
                    } else {
                        // Fight with robot at the new position
                        fight(robot, grid[newX][newY]);
                    }
                }
            }
        }
    }
}

void Simulation::fight(Robot* attacker, Robot* victim) {
    std::cout << "Fight between " << attacker->getName() << " and " << victim->getName() << std::endl;
    
    // Continue fight until one robot dies
    while (!attacker->isDead() && !victim->isDead()) {
        // Attacker attacks
        int damage = attacker->getDamage();
        int victimOldHP = victim->getHitpoints();
        victim->setHitpoints(victimOldHP - damage);
        
        // Display hit message
        std::cout << attacker->getName() << "(" << attacker->getHitpoints() << ") hits " 
                  << victim->getName() << "(" << victimOldHP << ") with " 
                  << damage << std::endl;
        std::cout << "The new hitpoints of " << victim->getName() << " is " << victim->getHitpoints() << std::endl;
        
        if (victim->isDead()) {
            std::cout << victim->getName() << " is destroyed!" << std::endl;
            break;
        }
        
        // Victim counter-attacks
        damage = victim->getDamage();
        int attackerOldHP = attacker->getHitpoints();
        attacker->setHitpoints(attackerOldHP - damage);
        
        // Display hit message
        std::cout << victim->getName() << "(" << victim->getHitpoints() << ") hits " 
                  << attacker->getName() << "(" << attackerOldHP << ") with " 
                  << damage << std::endl;
        std::cout << "The new hitpoints of " << attacker->getName() << " is " << attacker->getHitpoints() << std::endl;
        
        if (attacker->isDead()) {
            std::cout << attacker->getName() << " is destroyed!" << std::endl;
            break;
        }
        
        // Special case for Kamikaze - dies after attacking
        if (attacker->getType() == "kamikaze") {
            attacker->setHitpoints(0);
            std::cout << attacker->getName() << " self-destructs after attacking!" << std::endl;
            break;
        }
    }
}

bool Simulation::isGameOver() const {
    return robotCount <= 1;
}

void Simulation::healHumanicRobots() {
    for (auto robot : robots) {
        if (robot != nullptr && !robot->isDead() && 
            (robot->getType() == "optimusprime" || robot->getType() == "robocop")) {
            // Humanoid robots heal 1 hitpoint per turn
            robot->setHitpoints(robot->getHitpoints() + HUMANIC_HEAL_AMOUNT);
        }
    }
}

void Simulation::cleanupDeadRobots() {
    // Remove dead robots from the grid
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != nullptr && grid[i][j]->isDead()) {
                grid[i][j] = nullptr;
            }
        }
    }
    
    // Count remaining robots
    robotCount = 0;
    for (auto robot : robots) {
        if (robot != nullptr && !robot->isDead()) {
            robotCount++;
        }
    }
}

void Simulation::run() {
    createRobots();
    
    int step = 0;
    bool combatOccurred = false;
    
    while (!isGameOver()) {
        std::cout << "Step " << step++ << std::endl;
        displayGrid();
        
        // Process user input
        std::cout << "Press Enter for next step...";
        std::cin.get();
        
        // Continue moving until combat occurs or game ends
        combatOccurred = false;
        while (!combatOccurred && !isGameOver()) {
            combatOccurred = moveRobotsUntilCombat();
            
            // Heal humanoid robots
            healHumanicRobots();
            
            // Clean up dead robots
            cleanupDeadRobots();
        }
    }
    
    std::cout << "Simulation completed!" << std::endl;
    displayGrid();
    
    // Show the winner
    for (auto robot : robots) {
        if (robot != nullptr && !robot->isDead()) {
            std::cout << "The winner is: " << robot->getName() << " (" << robot->getType() << ")" << std::endl;
        }
    }
}

// New method to move robots until combat occurs
bool Simulation::moveRobotsUntilCombat() {
    // Reset moved flags
    for (auto robot : robots) {
        if (robot != nullptr) {
            robot->setMoved(false);
        }
    }
    
    // Move each robot
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != nullptr && !grid[i][j]->hasMoved()) {
                Robot* robot = grid[i][j];
                robot->setMoved(true);
                
                // Try to move
                int dir = rand() % 4; // 0: up, 1: right, 2: down, 3: left
                int newX = i, newY = j;
                
                switch (dir) {
                    case 0: newX--; break; // Up
                    case 1: newY++; break; // Right
                    case 2: newX++; break; // Down
                    case 3: newY--; break; // Left
                }
                
                // Check if new position is valid
                if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE) {
                    if (grid[newX][newY] == nullptr) {
                        // Move to empty cell
                        grid[newX][newY] = robot;
                        grid[i][j] = nullptr;
                    } else {
                        // Fight with robot at the new position
                        fight(robot, grid[newX][newY]);
                        return true; // Combat occurred
                    }
                }
            }
        }
    }
    
    return false; // No combat occurred
}