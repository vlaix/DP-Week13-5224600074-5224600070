#pragma once
#include "PokerHandChecker.h"

class StraightChecker : PokerHandChecker {
private:
    HandRank check(const Hand& hand) override;
};