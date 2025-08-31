#include "Robot.h"
#include <cstdlib>
#include <iostream>

// Default constructor
Robot::Robot() : 
    type(OPTIMUSPRIME), strength(0), hitpoints(0), name(""), moved(false) {}

// Parameterized constructor
Robot::Robot(RobotType newType, const std::string& newName) : 
    type(newType), 
    strength(ROBOT_ATTRIBUTES[newType].strength), 
    hitpoints(ROBOT_ATTRIBUTES[newType].hitpoints), 
    name(newName), 
    moved(false) {}

// Destructor
Robot::~Robot() {}

// Base damage calculation
int Robot::getDamage() const {
    // Basic damage calculation: random number between 0 and strength
    return (rand() % strength) + 1;
}

// Robot movement function
bool Robot::move(Robot*** grid, int gridSize) {
    int x = -1, y = -1;
    
    // Find this robot in the grid
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] == this) {
                x = i;
                y = j;
                break;
            }
        }
        if (x != -1) break;
    }
    
    if (x == -1) return false; // Robot not found in grid
    
    // Try to move in a random direction
    int dir = rand() % 4; // 0: up, 1: right, 2: down, 3: left
    int newX = x, newY = y;
    
    switch (dir) {
        case 0: newX--; break; // Up
        case 1: newY++; break; // Right
        case 2: newX++; break; // Down
        case 3: newY--; break; // Left
    }
    
    // Check if new position is valid
    if (newX >= 0 && newX < gridSize && newY >= 0 && newY < gridSize) {
        if (grid[newX][newY] == nullptr) {
            // Move to empty cell
            grid[newX][newY] = this;
            grid[x][y] = nullptr;
            return true;
        }
    }
    
    return false;
}