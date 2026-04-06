#pragma once
#include "PokerHandChecker.h"

class FullHouseChecker : PokerHandChecker {
private:
    HandRank check(const Hand& hand) override;
};