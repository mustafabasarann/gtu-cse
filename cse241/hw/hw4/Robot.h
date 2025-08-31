#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <iostream>
#include <cstdlib>
#include "Constants.h"

// Forward declaration
class Robot;

// Base Robot class
class Robot {
protected:
    RobotType type;     // Robot type
    int strength;       // Robot strength attribute
    int hitpoints;      // Robot health points
    std::string name;   // Robot name
    bool moved;         // Flag to track if robot has moved this turn
    
public:
    // Constructors
    Robot();
    Robot(RobotType newType, const std::string& newName);
    virtual ~Robot();
    
    // Accessors and mutators
    int getStrength() const { return strength; }
    int getHitpoints() const { return hitpoints; }
    void setHitpoints(int points) { hitpoints = points; }
    std::string getName() const { return name; }
    bool hasMoved() const { return moved; }
    void setMoved(bool m) { moved = m; }
    
    // Virtual functions
    virtual std::string getType() const = 0; // Pure virtual function
    virtual int getDamage() const;           // Virtual function with default implementation
    
    // Movement and state functions
    virtual bool move(Robot*** grid, int gridSize);
    bool isDead() const { return hitpoints <= 0; }
};

#endif