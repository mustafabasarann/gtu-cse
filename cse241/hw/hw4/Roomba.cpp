#include "Roomba.h"
#include <iostream>

// Constructor
Roomba::Roomba(const std::string& name) 
    : Robot(ROOMBA, name) {}

// Roomba damage calculation - attacks twice
int Roomba::getDamage() const {
    int damage1 = Robot::getDamage();
    int damage2 = Robot::getDamage();
    std::cout << getName() << " attacks twice for " << damage1 << " and " << damage2 << " damage!" << std::endl;
    return damage1 + damage2;
}

// Roomba can move twice
bool Roomba::move(Robot*** grid, int gridSize) {
    bool moved1 = Robot::move(grid, gridSize);
    bool moved2 = Robot::move(grid, gridSize);
    return moved1 || moved2;
}