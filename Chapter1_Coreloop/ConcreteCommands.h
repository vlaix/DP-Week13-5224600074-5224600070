#pragma once
#include "RewardCommand.h"
#include <string>

class BonusHandCommand : public RewardCommand {
public:
    void execute(GameSession& session) override;
    std::string getName() const override { return "Bonus Hand (+1 Hand Next Blind)"; }
};

class FreePlayingCard : public RewardCommand {
public:
    void execute(GameSession& session) override;
    std::string getName() const override { return "Free Playing Card"; }
};