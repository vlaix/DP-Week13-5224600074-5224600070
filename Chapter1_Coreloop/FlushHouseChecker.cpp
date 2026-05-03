#include <iostream>
#include "FlushHouseChecker.h"
#include "PokerHelper.h"

bool isFlushHouse(const Hand& hand)
{
    char suit = hand.cards[0].suit;

    for(const auto& card : hand.cards)
    {
        if(card.suit != suit)
        {
            return false;
        }
    }

    auto count = getRankCount(hand);

    bool hasThree = false;
    bool hasTwo = false;

    for(const auto& pair : count)
    {
        if(pair.second == 3)
        {
            hasThree = true;
        }

        if(pair.second == 2)
        {
            hasTwo = true;
        }
    }
    return hasThree && hasTwo;
}

HandRank FlushHouseChecker::check(const Hand& hand)
{
    if(isFlushHouse(hand))
    {
        std::cout << "Detected FLUSH HOUSE\n";
        return HandRank::FLUSH_HOUSE;
    }
    if(nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}