#include <iostream>
#include "PokerHelper.h"
#include "StraightFlushChecker.h"


bool isStraightFlush(const Hand& hand){

    return isFlush(hand)&&isStraight(hand);
}

HandRank StraightFlushChecker::check(const Hand& hand){
    if (isStraightFlush(hand)){
        std::cout << "Detected STRAIGHT FLUSH\n";
        return HandRank::STRAIGHT_FLUSH;
    }
    if (nextChecker)
        return nextChecker->check(hand);

    return HandRank::HIGH_CARD;
}