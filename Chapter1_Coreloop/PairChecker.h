#pragma once
#include "PokerHandChecker.h"

class PairChecker : public PokerHandChecker {
private:
    HandRank check(const Hand& hand) override;
};