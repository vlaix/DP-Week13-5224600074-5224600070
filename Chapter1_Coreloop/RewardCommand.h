#pragma once
#include <string>

class GameSession;

enum class RewardTiming {
    Start,
    NextBlind,
    NextAnte
};

class RewardCommand {
public:
    virtual ~RewardCommand() = default;
    virtual void execute(GameSession& session) = 0; 
    virtual std::string getName() const = 0; 
};