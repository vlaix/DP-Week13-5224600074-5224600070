#pragma once
#include "PokerHandChecker.h"

class TwoPairChecker : PokerHandChecker {
private:
    HandRank check(const Hand& hand) override;
};