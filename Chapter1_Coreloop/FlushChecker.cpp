#include <iostream>
#include "PokerHelper.h"
#include "FlushChecker.h"

HandRank FlushChecker::check(const Hand& hand){
    if (isFlush(hand)){
        std::cout << "Detected Flush\n";
        return HandRank::FLUSH;
    }
    if (nextChecker)
        return nextChecker->check(hand);
        
    return HandRank::HIGH_CARD;
}