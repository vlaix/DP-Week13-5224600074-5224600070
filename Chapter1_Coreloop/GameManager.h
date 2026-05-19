#pragma once
#include "HandGenerator.h"
#include "HandPlayer.h"
#include "ScoringRule.h"
#include "BlindRule.h"
#include "RewardRule.h"
#include "JokerManager.h"
#include "FlatChipJoker.h"
#include "PairJoker.h"

class GameManager {
public:
    GameManager();
    void runSession();

private:
    HandGenerator handGenerator;
    HandPlayer    handPlayer;
    ScoringRule   scoringRule;
    BlindRule     blindRule;
    RewardRule    rewardRule;
    JokerManager  jokerManager;
};