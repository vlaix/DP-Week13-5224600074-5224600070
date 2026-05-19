#include "JokerManager.h"
#include <iostream>

void JokerManager::addJoker(std::unique_ptr<Joker> joker)
{
    jokers.push_back(std::move(joker));
}

void JokerManager::applyJokers(ScoreContext& context) const
{
    std::cout << "\n=== Joker Effects ===\n";

    for (const auto& joker : jokers)
    {
        std::cout << joker->getName() << " : "
                  << joker->getDescription(context) << "\n";
        joker->onScoreCalculated(context);
        std::cout << "  chips=" << context.chips
                  << " mult=" << context.mult << "\n";
    }

    std::cout << "=== Final Score: "
              << context.chips << " x " << context.mult
              << " = " << context.getFinalScore() << " ===\n";
}