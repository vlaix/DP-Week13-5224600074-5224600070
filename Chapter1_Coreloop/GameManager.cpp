#include "GameManager.h"
#include "ConcreteCommands.h"
#include <iostream>

void GameManager::startGameLoop(GameSession& session) {
    std::cout << "=== WELCOME TO BALATRO SIMULATOR (SYSTEM STARTED) ===\n";
    while (true) {
        auto currentBlind = session.getCurrentBlind();
        std::cout << "\n============================================\n";
        std::cout << "Target Saat Ini: " << currentBlind->getBlindName() << " (Ante " << session.getAnte() << ")\n";
        std::cout << "Uangmu saat ini: $" << session.getMoney() << "\n";
        std::cout << "1. PLAY Blind (Kejar target skor " << currentBlind->getTargetScore() << ")\n";
        std::cout << "2. SKIP Blind (Lewati demi mendapatkan Reward)\n";
        std::cout << "3. EXIT Game\n";
        std::cout << "Pilih tindakan (1-3): ";
        
        int pilihan;
        std::cin >> pilihan;
        if (pilihan == 1) runSession(session);
        else if (pilihan == 2) skipBlind(session);
        else if (pilihan == 3) break;
    }
}

void GameManager::handleDiscard(GameSession& gameSession, Hand& currentHand) {
    std::cout << "\n--- PROSES DISCARD ---\n";
    // Memanggil playHand dengan passing reference (Hand&) agar kartu pilihan terhapus dari tangan utama
    Hand discardedCards = handPlayer.playHand(currentHand); 
    std::cout << "Membuang " << discardedCards.cards.size() << " kartu dari tangan...\n";
    
    gameSession.setRemainingDiscards(gameSession.getRemainingDiscards() - 1);
}

void GameManager::runSession(GameSession& gameSession) {
    std::cout << "\n=== Run Started ===\n";
    triggerRewards(gameSession, RewardTiming::NextBlind);
    triggerRewards(gameSession, RewardTiming::Start);

    auto activeBlind = gameSession.getCurrentBlind();
    std::cout << "Memasuki Sesi: " << activeBlind->getBlindName() << "\n";

    int currentRoundScore = 0;
    int playsLeft = gameSession.getRemainingPlays();
    gameSession.setRemainingDiscards(4); 
    
   while (currentRoundScore < activeBlind->getTargetScore() && playsLeft > 0) {
        Hand hand = handGenerator.generateHand(); 
        std::cout << "\n--------------------------------------------\n";
        std::cout << "Total Skor Ronde: " << currentRoundScore << " / " << activeBlind->getTargetScore() << "\n";
        std::cout << "Sisa Plays: " << playsLeft << " | Sisa Discards: " << gameSession.getRemainingDiscards() << "\n";
        
        std::cout << "\n=== Susunan Kartu di Tanganmu ===\n";
        for (size_t i = 0; i < hand.cards.size(); i++) {
            std::string rStr = (hand.cards[i].rank == 11) ? "J" : 
                               (hand.cards[i].rank == 12) ? "Q" : 
                               (hand.cards[i].rank == 13) ? "K" : 
                               (hand.cards[i].rank == 14) ? "A" : std::to_string(hand.cards[i].rank);
            std::cout << i+1 << ". " << hand.cards[i].suit << " " << rStr << "\n";
        }
        std::cout << "=================================\n";
    

        std::cout << "\nAksi:\n1. PLAY HAND (Tarungkan kombinasi)\n2. DISCARD (Buang kartu)\nPilih aksi (1/2): ";
        int opsiAksi;
        std::cin >> opsiAksi;

        if (opsiAksi == 1) {
            Hand chosenhand = handPlayer.playHand(hand); 

            int baseScore = scoringRule.scoreHand(chosenhand);
            HandRank rank = scoringRule.getLastRank();

            ScoreContext context{baseScore, 1, rank};
            jokerManager.applyJokers(context);

            int finalHandScore = context.getFinalScore();
            currentRoundScore += finalHandScore;
            
            std::cout << "\n* Tangan Berhasil Dimainkan! Mendapatkan +" << finalHandScore << " Skor *\n";
            playsLeft--; 

        } else if (opsiAksi == 2) {
            if (gameSession.getRemainingDiscards() > 0) {
                handleDiscard(gameSession, hand);
            } else {
                std::cout << "[PERINGATAN] Sisa kuota Discard habis! Kamu wajib PLAY hand.\n";
            }
        }
    }

    // EVALUASI AKHIR ROUND (Dinamis mengambil data target dari State)
    if (blindRule.checkBlind(currentRoundScore, gameSession)) {
        int reward = activeBlind->getRewardMoney(); 
        gameSession.addMoney(reward);
        std::cout << "Selamat! Babak dilewati. Uang didapat: $" << reward << "\n";
        Shop(gameSession);
        activeBlind->handleNextState(gameSession); // State Pattern looping progresi berjalan otomatis
    } else {
        std::cout << "GAME OVER! Kuota bermain habis sebelum target skor tercapai.\n";
    }
    std::cout << "=== Run Ended ===\n";
}

void GameManager::skipBlind(GameSession& gameSession) {
    auto activeBlind = gameSession.getCurrentBlind();
    std::cout << "\n=== SKIP BLIND: " << activeBlind->getBlindName() << " ===\n";
    std::unique_ptr<RewardCommand> reward = activeBlind->createSkipReward();
    std::cout << "Mendapatkan Reward Tertunda: " << reward->getName() << "\n";

    gameSession.addPendingCommand(std::move(reward), RewardTiming::NextBlind);
    activeBlind->handleNextState(gameSession);
}

void GameManager::triggerRewards(GameSession& session, RewardTiming currentTiming) {
    for (auto it = session.pendingCommands.begin(); it != session.pendingCommands.end(); ) {
        if (it->timing == currentTiming) {
            it->command->execute(session);
            it = session.pendingCommands.erase(it);
        } else {
            ++it;
        }
    }
}

void GameManager::Shop(GameSession& session) {
    std::cout << "=== SHOP MAMBU ===\n";
    std::cout << "1. Pair Joker (2 Koin)\n";
    std::cout << "2. Flat Chip Joker (2 Koin)\n";
    std::cout << "3. Tidak Beli Joker\n";
    std::cout << "Pilih Joker yang dibeli (1 atau 2): ";
    int mambu;
    std::cin >> mambu;
    if (mambu == 3) {
        return;
    } else if (session.getMoney() > 2) {
        if (mambu == 1) {
            jokerManager.addJoker(std::make_unique<PairJoker>());
            session.addMoney(-2);
        } else if (mambu == 2) {
            jokerManager.addJoker(std::make_unique<FlatChipJoker>());
            session.addMoney(-2);
        }
    } else {
        std::cout << "Uang Tidak Cukup\n";
    }
}
