#pragma once
#include "PokerHandChecker.h"

class FlushChecker : public PokerHandChecker {
private:
    HandRank check(const Hand& hand) override;
};