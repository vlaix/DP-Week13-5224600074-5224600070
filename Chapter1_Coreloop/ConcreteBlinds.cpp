#include "ConcreteBlinds.h"

void SmallBlindState::handleNextState(GameSession& session) {
    session.setBlindState(std::make_shared<BigBlindState>()); // Small -> Big
}

void BigBlindState::handleNextState(GameSession& session) {
    session.setBlindState(std::make_shared<BossBlindState>()); // Big -> Boss
}