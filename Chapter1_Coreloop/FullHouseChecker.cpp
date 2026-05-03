#include <iostream>
#include "PokerHelper.h"
#include "FullHouseChecker.h"
#include "PokerHelper.h"

HandRank FullHouseChecker::check(const Hand& hand){
    if (DuplicateChecker(hand, 3) && DuplicateChecker(hand, 2)){
        std::cout << "Detected FULL HOUSE\n";
        return HandRank::FULL_HOUSE;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}