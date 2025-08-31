#include "Kamikaze.h"

// Constructor
Kamikaze::Kamikaze(const std::string& name) 
    : Robot(KAMIKAZE, name) {}

// Kamikaze damage calculation - returns hitpoints
int Kamikaze::getDamage() const {
    return hitpoints;
}