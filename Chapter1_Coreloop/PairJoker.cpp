#include "PairJoker.h"

std::string PairJoker::getName() const
{
    return "Pair Joker";
}

std::string PairJoker::getDescription(const ScoreContext& context) const
{
    if (context.handRank == HandRank::PAIR)
    {
        return "Pair detected! +4 mult";
    }
    return "No effect";
}

void PairJoker::onScoreCalculated(ScoreContext& context)
{
    if (context.handRank == HandRank::PAIR)
    {
        context.mult += 4;
    }
}