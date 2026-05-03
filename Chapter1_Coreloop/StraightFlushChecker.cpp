#include <iostream>
#include <algorithm>
#include <vector>
#include "StraightFlushChecker.h"

bool isStraightFlush(const Hand& hand)
{
    char suit = hand.cards[0].suit;

    for(const auto& card : hand.cards)
    {
        if(card.suit != suit)
        {
            return false;
        }
    }

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

HandRank StraightFlushChecker::check(const Hand& hand)
{
    if(isStraightFlush(hand))
    {
        std::cout << "Detected STRAIGHT FLUSH\n";
        return HandRank::STRAIGHT_FLUSH;
    }
    if(nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}