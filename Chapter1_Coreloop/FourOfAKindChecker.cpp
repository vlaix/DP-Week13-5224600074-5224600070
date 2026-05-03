#include <iostream>
#include "PokerHelper.h"
#include "FourOfAKindChecker.h"

HandRank FourOfAKindChecker::check(const Hand& hand){
    if (DuplicateChecker(hand, 4)){
        std::cout << "Detected FOUR OF A KIND\n";
        return HandRank::FOUR_OF_A_KIND;
    }
    if (nextChecker)
        return nextChecker->check(hand);

    return HandRank::HIGH_CARD;
}