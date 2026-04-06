#pragma once
#include "PokerHandChecker.h"

class PairChecker : PokerHandChecker {
private:
    HandRank check(const Hand& hand) override;
};