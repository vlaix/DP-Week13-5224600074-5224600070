#include "ConcreteBlinds.h"
#include "ConcreteCommands.h"
#include <iostream>

// ---- 1. Small Blind Implementation ----
void SmallBlindState::handleNextState(GameSession& session) {
    std::cout << "[STATE] Berpindah dari Small Blind -> Big Blind.\n";
    session.setBlindState(std::make_shared<BigBlindState>());
}

std::unique_ptr<RewardCommand> SmallBlindState::createSkipReward() {
    return std::make_unique<BonusHandCommand>();
}

// ---- 2. Big Blind Implementation ----
void BigBlindState::handleNextState(GameSession& session) {
    std::cout << "[STATE] Berpindah dari Big Blind -> Boss Blind.\n";
    session.setBlindState(std::make_shared<BossBlindState>());
}

std::unique_ptr<RewardCommand> BigBlindState::createSkipReward() {
    return std::make_unique<FreePlayingCard>();
}

// ---- 3. Boss Blind Implementation ----
void BossBlindState::handleNextState(GameSession& session) {
    std::cout << "[STATE] Boss Blind Selesai! Mengocok ulang ke Small Blind & Naik Ante.\n";
    session.incrementAnte();
    session.setBlindState(std::make_shared<SmallBlindState>());
}

std::unique_ptr<RewardCommand> BossBlindState::createSkipReward() {
    return std::make_unique<BonusHandCommand>();
}