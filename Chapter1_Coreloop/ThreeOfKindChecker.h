#pragma once
#include "PokerHandChecker.h"

class ThreeOfKindChecker : public PokerHandChecker {
private:
    HandRank check(const Hand& hand) override;
};