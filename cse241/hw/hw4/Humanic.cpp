#include "Humanic.h"
#include <iostream>

// Default constructor
Humanic::Humanic() : Robot() {}

// Parameterized constructor
Humanic::Humanic(RobotType newType, const std::string& newName)
    : Robot(newType, newName) {}

// Damage calculation for humanoid robots
int Humanic::getDamage() const {
    // Get base damage from Robot class
    int damage = Robot::getDamage();
    
    // Chance of tactical nuke attack
    if (rand() % 100 < HUMANIC_NUKE_CHANCE) {
        std::cout << getName() << " launches tactical nuke!" << std::endl;
        damage += TACTICAL_NUKE_DAMAGE;
    }
    
    return damage;
}