#include <iostream>
#include "GameManager.h"
#include "GameSession.h"
#include "ConcreteBlinds.h"

int main() {
    GameManager manager;
    
    GameSession session(std::make_shared<SmallBlindState>());
    
    manager.startGameLoop(session); 

    return 0;
}