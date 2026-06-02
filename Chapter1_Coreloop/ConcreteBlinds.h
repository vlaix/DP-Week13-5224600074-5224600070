#pragma once
#include "BlindState.h"
#include "GameSession.h"
#include <iostream>

//Small Blind
class SmallBlindState : public BlindState {
public:
    std::string getBlindName() const override { return "Small Blind"; }
    int getTargetScore() const override { return 300; }
    int getRewardMoney() const override { return 3; }
    void handleNextState(GameSession& session) override; 
};

//2. Big Blind
class BigBlindState : public BlindState {
public:
    std::string getBlindName() const override { return "Big Blind"; }
    int getTargetScore() const override { return 800; }
    int getRewardMoney() const override { return 4; }
    void handleNextState(GameSession& session) override;
};

//3. Boss Blind
class BossBlindState : public BlindState {
public:
    std::string getBlindName() const override { return "Boss Blind"; }
    int getTargetScore() const override { return 2000; }
    int getRewardMoney() const override { return 5; }
    void handleNextState(GameSession& session) override {
        std::cout << ">>> Boss Blind Selesai! Ante Naik, Siklus Berulang. <<<\n";
        session.incrementAnte();
        session.setBlindState(std::make_shared<SmallBlindState>());
    }
};