#pragma once
#include "BlindState.h"
#include "GameSession.h"
#include <memory>

class RewardCommand; // Forward declaration

// ---- 1. Small Blind State ----
class SmallBlindState : public BlindState {
public:
    std::string getBlindName() const override { return "Small Blind"; }
    int getTargetScore() const override { return 30; }
    int getRewardMoney() const override { return 3; }
    void handleNextState(GameSession& session) override; 
    std::unique_ptr<RewardCommand> createSkipReward() override; 
};

// ---- 2. Big Blind State ----
class BigBlindState : public BlindState {
public:
    std::string getBlindName() const override { return "Big Blind"; }
    int getTargetScore() const override { return 60; }
    int getRewardMoney() const override { return 4; }
    void handleNextState(GameSession& session) override;
    std::unique_ptr<RewardCommand> createSkipReward() override; 
};

// ---- 3. Boss Blind State ----
class BossBlindState : public BlindState {
public:
    std::string getBlindName() const override { return "Boss Blind"; }
    int getTargetScore() const override { return 100; }
    int getRewardMoney() const override { return 5; }
    void handleNextState(GameSession& session) override;
    std::unique_ptr<RewardCommand> createSkipReward() override; 
};