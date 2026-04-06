#pragma once
#include "PokerHandChecker.h"

class HighCard : PokerHandChecker {
private:
    HandRank check(const Hand& hand) override;
};