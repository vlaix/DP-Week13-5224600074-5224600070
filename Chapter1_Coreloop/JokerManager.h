#pragma once
#include "Joker.h"
#include <vector>
#include <memory>

class JokerManager {
public:
    void addJoker(std::unique_ptr<Joker> joker);
    void applyJokers(ScoreContext& context) const;

private:
    std::vector<std::unique_ptr<Joker>> jokers;
};