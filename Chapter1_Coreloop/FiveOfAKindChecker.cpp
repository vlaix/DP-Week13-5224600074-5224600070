#include <iostream>
#include "PokerHelper.h"
#include "FiveOfAKindChecker.h"
#include "PokerHelper.h"

bool isFiveOfAKind(const Hand& hand){
    auto count = getRankCount(hand);

    for(const auto& pair : count)
        if(pair.second == 5) return true;
    return false;
}

HandRank FiveOfAKindChecker::check(const Hand& hand){
    if (DuplicateChecker(hand, 5)){
        std::cout << "Detected FIVE OF A KIND\n";
        return HandRank::FIVE_OF_A_KIND;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}