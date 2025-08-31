#ifndef OPTIMUSPRIME_H
#define OPTIMUSPRIME_H

#include "Humanic.h"
#include "Constants.h"

// OptimusPrime class - inherits from Humanic
class OptimusPrime : public Humanic {
public:
    OptimusPrime(const std::string& name);
    
    std::string getType() const override { return "optimusprime"; }
    int getDamage() const override;
};

#endif