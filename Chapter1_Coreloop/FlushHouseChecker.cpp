#include <iostream>
#include "PokerHelper.h"
#include "FlushHouseChecker.h"
#include "PokerHelper.h"

HandRank FlushHouseChecker::check(const Hand& hand){
    if (DuplicateChecker(hand, 3) && DuplicateChecker(hand, 2) && isFlush(hand)){
        std::cout << "Detected FLUSH HOUSE\n";
        return HandRank::FLUSH_HOUSE;
    }
    if(nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}