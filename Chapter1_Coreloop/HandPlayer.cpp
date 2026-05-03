#include <iostream>
#include "HandPlayer.h"

Hand HandPlayer::playHand(Hand hand)
{
    ChosenHand chooser;
    std::cout << "Player selects cards to play...\n";
    return chooser.chooseCards(hand);
}   