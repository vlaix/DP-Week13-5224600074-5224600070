#include <iostream>
#include "PokerHelper.h"
#include "StraightChecker.h"

HandRank StraightChecker::check(const Hand& hand){
    if (isStraight(hand)){
        std::cout << "Detected STRAIGHT\n";
        return HandRank::STRAIGHT;
    }
    if(nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}