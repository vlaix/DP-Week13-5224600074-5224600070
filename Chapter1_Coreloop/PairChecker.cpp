#include <iostream>
#include <map>
#include "PairChecker.h"
#include "PokerHelper.h"

bool isPair(const Hand& hand)
{
    auto count = getRankCount(hand);

    int pairCount = 0;

    for(const auto& pair : count)
    {
        if(pair.second == 2)
        {
            pairCount++;
        }
    }
    return pairCount == 1;
}

HandRank PairChecker::check(const Hand& hand){
    if (isPair(hand)){
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