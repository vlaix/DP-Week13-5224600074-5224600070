#include <iostream>
#include "FlushFiveChecker.h"
#include "PokerHelper.h"

bool isFlushFive(const Hand& hand)
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

    for(const auto& pair : count)
    {
        if(pair.second == 5)
        {
            return true;
        }
    }
    return false;
}

HandRank FlushFiveChecker::check(const Hand& hand)
{
    if(isFlushFive(hand))
    {
        std::cout << "Detected FLUSH FIVE\n";
        return HandRank::FLUSH_FIVE;
    }
    if(nextChecker)
        return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}