#include "PokerHelper.h"

std::map<int, int> getRankCount(const Hand& hand)
{
    std::map<int, int> count;

    for(const Card& card : hand.cards)
    {
        count[card.rank]++;
    }

    return count;
}