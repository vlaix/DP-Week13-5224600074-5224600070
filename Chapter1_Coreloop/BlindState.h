#pragma once
#include <string>
#include <memory>

class GameSession;

class BlindState {
public:
    virtual ~BlindState() = default;
    virtual std::string getBlindName() const = 0;
    virtual int getTargetScore() const = 0;
    virtual int getRewardMoney() const = 0;
    virtual void handleNextState(GameSession& session) = 0;
};