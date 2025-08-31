#ifndef ROBOCOP_H
#define ROBOCOP_H

#include "Humanic.h"

// RoboCop class - inherits from Humanic
class RoboCop : public Humanic {
public:
    RoboCop(const std::string& name);
    
    std::string getType() const override { return "robocop"; }
    // Uses Humanic's getDamage implementation
};

#endif