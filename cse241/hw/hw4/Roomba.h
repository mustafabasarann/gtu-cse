#ifndef ROOMBA_H
#define ROOMBA_H

#include "Robot.h"

// Roomba class - inherits from Robot
class Roomba : public Robot {
public:
    Roomba(const std::string& name);
    
    std::string getType() const override { return "roomba"; }
    int getDamage() const override;
    bool move(Robot*** grid, int gridSize) override;
};

#endif