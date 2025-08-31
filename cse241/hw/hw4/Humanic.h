#ifndef HUMANIC_H
#define HUMANIC_H

#include "Robot.h"

// Humanic class - inherits from Robot, base for humanoid robots
class Humanic : public Robot {
public:
    Humanic();
    Humanic(RobotType newType, const std::string& newName);
    
    // Humanoid robots have chance of tactical nuke
    int getDamage() const override;
};

#endif