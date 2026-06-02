#include "HandGenerator.h"
#include <iostream>
#include <algorithm>
#include <ctime>

HandGenerator::HandGenerator() {
    gen.seed(static_cast<unsigned int>(std::time(0)));
    initializeDeck();
}

void HandGenerator::initializeDeck() {
    char Suit[4] = {'H', 'D', 'C', 'S'};
    gameDeck.cards.clear();
    for(int s = 0; s < 4; s++) {
        for(int r = 2; r <= 14; r++) {
            gameDeck.cards.push_back({r, Suit[s]});
        }
    }
    std::shuffle(gameDeck.cards.begin(), gameDeck.cards.end(), gen);
}

Hand HandGenerator::generateHand() {
    if (gameDeck.cards.size() < 8) initializeDeck();
    Hand hand;
    for(int i = 0; i < 8; i++) {
        Card buffer = gameDeck.cards.back();
        gameDeck.cards.pop_back();
        hand.cards.push_back(buffer);
    }
    return hand;
}

void HandGenerator::replenishHand(Hand& playerHand) {
    const int MAX_HAND_SIZE = 8;
    int cardsNeeded = MAX_HAND_SIZE - playerHand.cards.size();

    if (cardsNeeded <= 0) return; 

    std::cout << "\n[SYSTEM] Mengisi tangan kembali... Menarik " << cardsNeeded << " kartu dari deck.\n";

    for(int i = 0; i < cardsNeeded; i++) {
        if (gameDeck.cards.empty()) initializeDeck();
        Card newCard = gameDeck.cards.back();
        gameDeck.cards.pop_back();
        playerHand.cards.push_back(newCard);
    }

    std::cout << "\n=== Susunan Kartu Terbaru di Tanganmu ===\n";
    for (size_t i = 0; i < playerHand.cards.size(); i++) {
        std::string rankStr;
        switch(playerHand.cards[i].rank) {
            case 11: rankStr = "J"; break;
            case 12: rankStr = "Q"; break;
            case 13: rankStr = "K"; break;
            case 14: rankStr = "A"; break;
            default: rankStr = std::to_string(playerHand.cards[i].rank); break;
        }
        std::cout << i+1 << ". " << playerHand.cards[i].suit << " " << rankStr << "\n";
    }
    std::cout << "======================================\n";
}