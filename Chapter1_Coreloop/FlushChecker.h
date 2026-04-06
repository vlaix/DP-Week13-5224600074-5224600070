#pragma once
#include "PokerHandChecker.h"

class FlushChecker : PokerHandChecker {
private:
    HandRank check(const Hand& hand) override;
};