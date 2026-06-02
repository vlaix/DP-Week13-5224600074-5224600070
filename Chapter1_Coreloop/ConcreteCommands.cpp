#include "ConcreteCommands.h"
#include "GameSession.h"
#include <iostream>

void BonusHandCommand::execute(GameSession& session) {
    session.setRemainingPlays(session.getRemainingPlays() + 1); 
    std::cout << "[EFFECT] BonusHandCommand Aktif: Sisa Plays bertambah +1!\n";
}

void FreePlayingCard::execute(GameSession& session) {
    std::cout << "[EFFECT] FreePlayingCard Aktif: Kartu gratis ditambahkan ke Deck!\n";
}