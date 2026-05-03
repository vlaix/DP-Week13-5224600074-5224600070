#include <iostream>
#include <algorithm>
#include <vector>
#include "RoyalFlushChecker.h"

bool isRoyalFlush(const Hand& hand)
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

    std::vector<int> royal = {10, 11, 12, 13, 14};
    return ranks == royal;
}

HandRank RoyalFlushChecker::check(const Hand& hand)
{
    if(isRoyalFlush(hand))
    {
        std::cout << "Detected ROYAL FLUSH\n";
        return HandRank::ROYAL_FLUSH;
    }
    if(nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}