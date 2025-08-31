#ifndef BULLDOZER_H
#define BULLDOZER_H

#include "Robot.h"

// Bulldozer class - inherits from Robot
class Bulldozer : public Robot {
public:
    Bulldozer(const std::string& name);
    
    std::string getType() const override { return "bulldozer"; }
    // Uses Robot's getDamage implementation
};

#endif