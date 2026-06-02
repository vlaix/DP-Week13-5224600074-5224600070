// BlindRule.cpp
#include "BlindRule.h"
#include "GameSession.h"
#include <iostream>

bool BlindRule::checkBlind(int currentRoundScore, const GameSession& gameSession) {
    // Ambil state blind yang sedang aktif dari session runtime
    auto activeBlind = gameSession.getCurrentBlind();
    
    if (!activeBlind) {
        std::cout << "[ERROR] Tidak ada Blind aktif di dalam session!\n";
        return false;
    }

    int target = activeBlind->getTargetScore();

    std::cout << "\n=== EVALUASI RONDE ===\n";
    std::cout << "Skor Akhirmu : " << currentRoundScore << "\n";
    std::cout << "Target Blind : " << target << "\n";

    if (currentRoundScore >= target) {
        std::cout << ">> HASIL: BERHASIL MELEWATI TARGET! <<\n";
        return true;
    } else {
        std::cout << ">> HASIL: GAGAL MENCAPAI TARGET! <<\n";
        return false;
    }
}