#include <iostream>
#include "ThreeOfKindChecker.h"
#include "PokerHelper.h"

HandRank ThreeOfKindChecker::check(const Hand& hand){
    if (DuplicateChecker(hand, 3)){
        std::cout << "Detected THREE OF KIND\n";
        return HandRank::THREE_OF_A_KIND;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}