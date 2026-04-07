#pragma once
#include "PokerHandChecker.h"

class TwoPairChecker : public PokerHandChecker {
private:
    HandRank check(const Hand& hand) override;
};