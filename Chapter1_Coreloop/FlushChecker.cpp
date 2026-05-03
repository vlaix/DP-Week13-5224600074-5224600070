#include <iostream>
#include "FlushChecker.h"

bool isFlush(const Hand& hand){
    
    char suit = hand.cards[0].suit;

    for(const auto& card : hand.cards)
    {
        if(card.suit != suit)
        {
            return false;
        }
    }

    return true;
}

HandRank FlushChecker::check(const Hand& hand){
    if (isFlush(hand)){
        std::cout << "Detected Flush\n";
        return HandRank::FLUSH;
    }
    if (nextChecker)
        return nextChecker->check(hand);
        
    return HandRank::HIGH_CARD;
}