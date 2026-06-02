#include <iostream>
#include "HandPlayer.h"

Hand HandPlayer::playHand(Hand& hand)
{
    ChosenHand chooser;
    std::cout << "Player selects cards to play...\n";
    
    // Melempar reference 'hand' asli ke dalam chooser
    return chooser.chooseCards(hand);
}