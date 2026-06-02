#pragma once
#include <memory>
#include <vector>
#include "BlindState.h"
#include "RewardCommand.h"

class GameSession {
public:
    struct PendingCommand {
        std::unique_ptr<RewardCommand> command;
        RewardTiming timing;
    };

private:
    std::shared_ptr<BlindState> currentBlind;
    int currentAnte;
    int totalScore;
    int remainingPlays;
    int remainingDiscards;
    int money;

public:
    GameSession(std::shared_ptr<BlindState> initialBlind) 
        : currentBlind(initialBlind), currentAnte(1), totalScore(0), 
          remainingPlays(4), remainingDiscards(4), money(0) {}

    std::vector<PendingCommand> pendingCommands; 

    std::shared_ptr<BlindState> getCurrentBlind() const { return currentBlind; }
    void setBlindState(std::shared_ptr<BlindState> nextBlind) { currentBlind = nextBlind; }
    
    int getAnte() const { return currentAnte; }
    void incrementAnte() { currentAnte++; }

    int getRemainingPlays() const { return remainingPlays; }
    void setRemainingPlays(int amount) { remainingPlays = amount; }

    int getRemainingDiscards() const { return remainingDiscards; }
    void setRemainingDiscards(int amount) { remainingDiscards = amount; }

    void addMoney(int amount) { money += amount; }
    int getMoney() const { return money; }

    void addPendingCommand(std::unique_ptr<RewardCommand> cmd, RewardTiming timing) {
        pendingCommands.push_back({ std::move(cmd), timing });
    }
};