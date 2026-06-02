#pragma once
#include "Hand.h"
#include <random>

class HandGenerator {
private:
    Hand gameDeck; 
    std::mt19937 gen;
    void initializeDeck(); 

public:
    HandGenerator(); 
    Hand generateHand();
    void replenishHand(Hand& playerHand); 
};