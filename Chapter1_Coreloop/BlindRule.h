#pragma once
class GameSession;

class BlindRule {
public:
    BlindRule() = default;
    
    // Mengembalikan true jika skor memenuhi target Blind saat ini
    bool checkBlind(int currentRoundScore, const GameSession& gameSession);
};