#pragma once
#include "Hand.h"
#include "PokerHandChecker.h"

struct ScoreContext {
    int chips = 0;
    int mult  = 1;
    HandRank handRank = HandRank::HIGH_CARD;

    int getFinalScore() const { return chips * mult; }
};

class JokerObserver {
public:
    virtual ~JokerObserver() = default;
    virtual void onScoreCalculated(ScoreContext& context) = 0;
};