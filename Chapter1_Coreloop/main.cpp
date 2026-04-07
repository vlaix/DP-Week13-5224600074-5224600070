#include <iostream>
#include "GameManager.h"

int main()
{
    int buffer;
    GameManager gameManager;
    gameManager.runSession();

    std::cin >> buffer;
    return 0;
}