#include <iostream>
#include "FullHouseChecker.h"

// dummy helper
bool isFlush(const Hand& hand){
return hand.value == 7;
}

HandRank FullHouseChecker::check(const Hand& hand){
    if (isFlush(hand)){
        std::cout << "Detected FULL HOUSE\n";
        return HandRank::FULL_HOUSE;
    }
    if (nextChecker)
        return nextChecker->check(hand);
        
    return HandRank::HIGH_CARD;
}