#pragma once
#include "PokerHandChecker.h"

class ThreeOfKindChecker : PokerHandChecker {
private:
    HandRank check(const Hand& hand) override;
};