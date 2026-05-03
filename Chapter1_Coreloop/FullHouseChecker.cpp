#include <iostream>
#include "FullHouseChecker.h"
#include "PokerHelper.h"

bool isFullHouse(const Hand& hand){
    auto count = getRankCount(hand);

    bool hasThree = false;
    bool hasTwo = false;

    for(const auto& pair : count){
        if(pair.second == 3) 
        {
            hasThree = true;
        }
        if(pair.second == 2) 
        {
            hasTwo = true;
        }
    }
    return hasThree && hasTwo;
}

HandRank FullHouseChecker::check(const Hand& hand){
    if (isFullHouse(hand)){
        std::cout << "Detected FULL HOUSE\n";
        return HandRank::FULL_HOUSE;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}