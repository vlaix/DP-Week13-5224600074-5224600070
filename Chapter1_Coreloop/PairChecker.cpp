#include <iostream>
#include <map>
#include "PairChecker.h"
#include "PokerHelper.h"

HandRank PairChecker::check(const Hand& hand){
    if (DuplicateChecker(hand, 2)){
        std::cout << "Detected PAIR\n";
        return HandRank::PAIR;
    }
    if (nextChecker) {  
        return nextChecker->check(hand);
    } else {
        std::cout << "Detected HIGH CARD\n";
        return HandRank::HIGH_CARD;
    }
}