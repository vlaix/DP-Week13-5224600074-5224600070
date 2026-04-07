#include <iostream>
#include "ThreeOfKindChecker.h"

// dummy helper
bool isThreeOfKind(const Hand& hand){
return hand.value == 4;
}

HandRank ThreeOfKindChecker::check(const Hand& hand){
    if (isThreeOfKind(hand)){
        std::cout << "Detected THREE OF A KIND\n";
        return HandRank::THREE_OF_A_KIND;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    
        return HandRank::HIGH_CARD;
}