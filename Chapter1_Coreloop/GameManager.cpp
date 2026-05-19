#include <iostream>
#include "GameManager.h"

GameManager::GameManager()
{
    // tambah joker di sini
    jokerManager.addJoker(std::make_unique<PairJoker>());
    jokerManager.addJoker(std::make_unique<FlatChipJoker>());
}

void GameManager::runSession()
{
    std::cout << "=== Run Started ===\n";

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
    int reward  = rewardRule.earnMoney(win, finalScore);

    std::cout << "Money gained: " << reward << "\n";
    std::cout << "=== Run Ended ===\n";
}