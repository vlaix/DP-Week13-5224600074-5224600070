#include <iostream>
#include "HandGenerator.h"

Hand HandGenerator::generateHand(){
    int buffer;
    std::cout << "Input cards for player: ";
    std::cin >> buffer;
    std::cout << "\n";
    
    Hand hand;
    hand.value = buffer;
    return hand;
}