#include <iostream>
#include "FourOfAKindChecker.h"
#include "PokerHelper.h"

bool isFourOfAKind(const Hand& hand){
    auto count = getRankCount(hand);

    for(const auto& pair : count)
        if(pair.second == 4) return true;
    return false;
}

HandRank FourOfAKindChecker::check(const Hand& hand){
    if (isFourOfAKind(hand)){
        std::cout << "Detected FOUR OF A KIND\n";
        return HandRank::FOUR_OF_A_KIND;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}