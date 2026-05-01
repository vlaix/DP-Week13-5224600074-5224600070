#include <iostream>
#include <algorithm> // Wajib untuk std::shuffle
#include <random>    // Wajib untuk std::mt19937
#include <ctime>     // Wajib untuk std::time
#include "Card.h"
#include "HandGenerator.h"

Hand HandGenerator::generateHand()
{
    std::cout << "Generating hand...\n";
    char Suit[4] = {'H', 'D', 'C', 'S'}; //heart, diamond, club, spade
    Hand deck;
    Hand hand;

    //bikin kartu dideck
    for(int s = 0; s < 4; s++)
    {
        for(int r = 2; r <= 14; r++)
        {
            deck.cards.push_back({r,Suit[s]});
        }
    }

    //shuffle kartu
    static std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
    std::shuffle(deck.cards.begin(), deck.cards.end(), gen);

    std::cout << "===Kartu di dapat===\n";

    //memberi pemain 8 kartu untuk dipilih
    for(int i = 0; i < 8; i++)
    {
        Card buffer = deck.cards.back();
        std::string bufferRank;

        switch(buffer.rank)
        {
            case 11: bufferRank = "J"; break;
            case 12: bufferRank = "Q"; break;
            case 13: bufferRank = "K"; break;
            case 14: bufferRank = "A"; break;
            default: bufferRank = std::to_string(buffer.rank); break;
        }

        hand.cards.push_back(buffer);
        std::cout << i+1 << ". " << buffer.suit << " " << bufferRank << "\n";
        deck.cards.pop_back();
    }
        
    return hand;
}

