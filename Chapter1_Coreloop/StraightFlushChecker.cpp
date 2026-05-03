#include <iostream>
#include "PokerHelper.h"
#include "StraightFlushChecker.h"

HandRank StraightFlushChecker::check(const Hand& hand){
    if(isFlush(hand) && isStraight(hand))
    {
        std::cout << "Detected STRAIGHT FLUSH\n";
        return HandRank::STRAIGHT_FLUSH;
    }
    if(nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}