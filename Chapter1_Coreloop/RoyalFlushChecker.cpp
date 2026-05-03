#include <iostream>
#include "PokerHelper.h"
#include "RoyalFlushChecker.h"

// dummy helper
bool isRoyalFlush(const Hand& hand){
    if(!isFlush(hand) || !isStraight(hand))
    {
        return false;
    }

    int ranks[5];

    for(int i = 0; i < 5; i++)
    {
        ranks[i] = hand.cards[i].rank;
    }

    std::sort(ranks, ranks + 5);

    return ranks[0] == 10;
}

HandRank RoyalFlushChecker::check(const Hand& hand){
    if (isRoyalFlush(hand)){
        std::cout << "Detected ROYAL FLUSH\n";
        return HandRank::ROYAL_FLUSH;
    }
    if (nextChecker)
        return nextChecker->check(hand);

    return HandRank::HIGH_CARD;
}