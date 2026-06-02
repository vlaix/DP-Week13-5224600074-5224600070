#pragma once
#include "GameSession.h"
#include "HandGenerator.h"
#include "HandPlayer.h"
#include "ScoringRule.h"
#include "JokerManager.h"
#include "BlindRule.h"

class GameManager {
private:
    HandGenerator handGenerator;
    HandPlayer handPlayer;
    ScoringRule scoringRule;
    JokerManager jokerManager;
    BlindRule blindRule;

    // Fungsi internal (pribadi) untuk memproses alur gameplay
    void runSession(GameSession& gameSession);
    void skipBlind(GameSession& gameSession);
    void handleDiscard(GameSession& gameSession, Hand& currentHand);
    void triggerRewards(GameSession& gameSession, RewardTiming currentTiming);

public:
    GameManager() = default;
    
    // Fungsi utama yang dipanggil dari main.cpp
    void startGameLoop(GameSession& session); 
};