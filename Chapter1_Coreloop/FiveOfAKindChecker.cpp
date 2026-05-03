#include <iostream>
#include "PokerHelper.h"
#include "FiveOfAKindChecker.h"

HandRank FiveOfAKindChecker::check(const Hand& hand){
    if (DuplicateChecker(hand, 5)){
        std::cout << "Detected FIVE OF A KIND\n";
        return HandRank::FIVE_OF_A_KIND;
    }
    if (nextChecker)
        return nextChecker->check(hand);

    return HandRank::HIGH_CARD;
}