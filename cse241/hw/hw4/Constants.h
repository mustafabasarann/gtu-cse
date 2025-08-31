#ifndef CONSTANTS_H
#define CONSTANTS_H

// Grid size constant
const int GRID_SIZE = 10;

// Initial robot counts
const int INITIAL_COUNT_EACH_TYPE = 5;

// Robot types
enum RobotType {
    OPTIMUSPRIME = 0,
    ROBOCOP = 1,
    ROOMBA = 2,
    BULLDOZER = 3,
    KAMIKAZE = 4
};

// Robot initial attributes
struct RobotAttributes {
    int strength;
    int hitpoints;
};

// Initial attributes for each robot type
const RobotAttributes ROBOT_ATTRIBUTES[] = {
    {100, 100}, // OPTIMUSPRIME
    {30, 40},   // ROBOCOP
    {3, 10},    // ROOMBA
    {50, 200},  // BULLDOZER
    {10, 10}    // KAMIKAZE
};

// Combat chances
const int HUMANIC_NUKE_CHANCE = 15;    // 15% chance
const int OPTIMUSPRIME_STRONG_ATTACK_CHANCE = 20;  // 20% chance

// Special damage values
const int TACTICAL_NUKE_DAMAGE = 40;

// Healing
const int HUMANIC_HEAL_AMOUNT = 1;

#endif