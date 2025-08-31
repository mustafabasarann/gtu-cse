#include "RoboCop.h"

// Constructor
RoboCop::RoboCop(const std::string& name) 
    : Humanic(ROBOCOP, name) {}

// RoboCop uses the default Humanic getDamage implementation