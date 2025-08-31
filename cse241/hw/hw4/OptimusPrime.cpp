#include "OptimusPrime.h"
#include <iostream>

// Constructor
OptimusPrime::OptimusPrime(const std::string& name) 
    : Humanic(OPTIMUSPRIME, name) 
{
}

// OptimusPrime damage calculation
int OptimusPrime::getDamage() const 
{
    // Get base damage from Humanic class (includes tactical nuke chance)
    int damage = Humanic::getDamage();
    
    // Chance of strong attack (double damage)
    if (rand() % 100 < OPTIMUSPRIME_STRONG_ATTACK_CHANCE) {
        std::cout << getName() << " performs a strong attack!" << std::endl;
        damage *= 2;
    }
    
    return damage;
}