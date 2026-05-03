#include <iostream>
#include <algorithm>
#include <vector>
#include "StraightChecker.h"

bool isStraight(const Hand& hand)
{
    std::vector<int> ranks;

    for(const auto& card : hand.cards)
    {
        ranks.push_back(card.rank);
    }

    std::sort(ranks.begin(), ranks.end());

    for(int i = 1; i < (int)ranks.size(); i++)
    {
        if(ranks[i] != ranks[i-1] + 1)
        {
            return false;
        }
    }
    return true;
}

HandRank StraightChecker::check(const Hand& hand)
{
    if(isStraight(hand))
    {
        std::cout << "Detected STRAIGHT\n";
        return HandRank::STRAIGHT;
    }
    if(nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}