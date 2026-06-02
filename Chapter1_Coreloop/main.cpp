#include <iostream>
#include "GameManager.h"
#include "GameSession.h"
#include "ConcreteBlinds.h"

int main()
{
    int buffer;
    GameManager gameManager;

    auto initialState = std::make_shared<SmallBlindState>();

    GameSession gameSession(initialState);

    gameManager.runSession(gameSession);

    gameManager.runSession(gameSession);

    std::cin >> buffer;
    return 0;
}