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

bool isFlush(const Hand& hand)
{
    char suit = hand.cards[0].suit;

    for(const Card& card : hand.cards)
    {
        if(card.suit != suit)
        {
            return false;
        }
    }

    return true;
}

bool isStraight(const Hand& hand){

    int CardRank[5];

    for(int i = 0; i < 5; i++)
    {
        CardRank[i] = hand.cards[i].rank;
    }

    std::sort(CardRank,CardRank + 5);

    for(int i = 0; i < 4; i++)
    {
        if(CardRank[i] + 1 != CardRank[i + 1])
        {
            return false;
        }
    }

    return true;
}

bool DuplicateChecker(const Hand& hand, int Many){
    auto count = getRankCount(hand);
    for(const auto& pair : count)
    {
        if(pair.second == Many)
        {
            return true;
        }
    }
    return false;
}