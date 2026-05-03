#include <iostream>
#include "ThreeOfKindChecker.h"
#include "PokerHelper.h"

bool isThreeOfKind(const Hand& hand)
{
    auto count = getRankCount(hand);

    bool hasThree = false;
    bool hasPair = false;

    for(const auto& pair : count)
    {
        if(pair.second == 3)
        {
            hasThree = true;
        }

        if(pair.second == 2)
        {
            hasPair = true;
        }
    }

    return hasThree && !hasPair;
}

HandRank ThreeOfKindChecker::check(const Hand& hand){
    if (isThreeOfKind(hand)){
        std::cout << "Detected THREE OF KIND\n";
        return HandRank::THREE_OF_A_KIND;
    }
    if (nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}