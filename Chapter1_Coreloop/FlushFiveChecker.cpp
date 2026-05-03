#include <iostream>
#include "PokerHelper.h"
#include "FlushFiveChecker.h"

HandRank FlushFiveChecker::check(const Hand& hand){
    if (isFlush(hand) && DuplicateChecker(hand, 5)){
        std::cout << "Detected FLUSH FIVE\n";
        return HandRank::FLUSH_FIVE;
    }
    if (nextChecker)
        return nextChecker->check(hand);

    return HandRank::HIGH_CARD;
}