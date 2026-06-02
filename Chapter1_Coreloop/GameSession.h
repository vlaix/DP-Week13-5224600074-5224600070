#pragma once
#include <memory>
#include "BlindState.h"

class GameSession {
private:
    std::shared_ptr<BlindState> currentBlind;
    int currentAnte;
    int money;

public:
    GameSession(std::shared_ptr<BlindState> initialBlind) 
        : currentBlind(initialBlind), currentAnte(1), money(0) {}

    std::shared_ptr<BlindState> getCurrentBlind() const { return currentBlind; }
    void setBlindState(std::shared_ptr<BlindState> nextBlind) { currentBlind = nextBlind; }
    
    int getAnte() const { return currentAnte; }
    void incrementAnte() { currentAnte++; }
    
    void addMoney(int amount) { money += amount; }
    int getMoney() const { return money; }
};