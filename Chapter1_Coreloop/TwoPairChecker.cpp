#include <iostream>
#include <map>
#include "TwoPairChecker.h"
#include "PokerHelper.h"

bool isTwoPair(const Hand& hand){
    auto count = getRankCount(hand);

    int pairCount = 0;

    for(const auto& pair : count)
    {
        if(pair.second == 2)
        {
            pairCount++;
        }
    }
    return pairCount == 2;
}

HandRank TwoPairChecker::check(const Hand& hand){
    if (isTwoPair(hand)){
        std::cout << "Detected TWO PAIR\n";
        return HandRank::TWO_PAIR;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}