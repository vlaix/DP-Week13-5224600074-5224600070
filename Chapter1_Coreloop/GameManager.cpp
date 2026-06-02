#include <iostream>
#include "GameManager.h"

GameManager::GameManager()
{
    // tambah joker di sini
    jokerManager.addJoker(std::make_unique<PairJoker>());
    jokerManager.addJoker(std::make_unique<FlatChipJoker>());
}

void GameManager::runSession(GameSession& gameSession)
{
    std::cout << "=== Run Started ===\n";

    auto activeBlind = gameSession.getCurrentBlind();
    std::cout << "Memasuki: " << activeBlind->getBlindName() << "\n";

    Hand hand       = handGenerator.generateHand();
    Hand chosenhand = handPlayer.playHand(hand);

    int baseScore   = scoringRule.scoreHand(chosenhand);
    HandRank rank   = scoringRule.getLastRank();

    // buat context untuk joker
    ScoreContext context;
    context.chips    = baseScore;
    context.mult     = 1;
    context.handRank = rank;

    // apply semua joker
    jokerManager.applyJokers(context);

    int finalScore = context.getFinalScore();

    bool win    = blindRule.checkBlind(finalScore);
    
    if (win) {
        int reward = activeBlind->getRewardMoney(); // Ambil uang dari state aktif
        gameSession.addMoney(reward);
        std::cout << "Money gained: " << reward << "\n";

        // State otomatis berubah di dalam session
        activeBlind->handleNextState(gameSession); 
    } else {
        std::cout << "Game Over.\n";
    }
    std::cout << "=== Run Ended ===\n";
}