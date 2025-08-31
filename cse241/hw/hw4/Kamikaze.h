#ifndef KAMIKAZE_H
#define KAMIKAZE_H

#include "Robot.h"

// Kamikaze class - inherits from Robot
class Kamikaze : public Robot {
public:
    Kamikaze(const std::string& name);
    
    std::string getType() const override { return "kamikaze"; }
    int getDamage() const override;
};

#endif