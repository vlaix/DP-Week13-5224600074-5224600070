#include <iostream>
#include "HandGenerator.h"

Hand HandGenerator::generateHand(){
    int buffer;
    std::cout << "Input cards for player: ";
    std::cin >> buffer;
    
    Hand hand;
    hand.value = buffer;
    return hand;
}