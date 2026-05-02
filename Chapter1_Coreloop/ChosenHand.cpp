#include <iostream>
#include <set>
#include "ChosenHand.h"

Hand ChosenHand::chooseCards(const Hand& hand){
    std::set<int> chosen;

    std::cout << "Pilih 5 kartu (masukkan nomor 1-8, pisahkan spasi): ";

    while (chosen.size() < 5){
        int input;
        std::cin >> input;

        if (input < 1 || input > 8){
            std::cout << "Nomor tidak valid, masukkan angka 1-8\n";
            continue;
        }

        if (chosen.count(input)){
            std::cout << "Kartu " << input << " sudah dipilih\n";
            continue;
        }

        chosen.insert(input);
    }

    Hand result;
    for (int idx : chosen){
        result.cards.push_back(hand.cards[idx - 1]);
    }

    std::cout << "===Kartu dipilih===\n";
    for (auto& card : result.cards){
        std::string rankStr;
        switch(card.rank){
            case 11: rankStr = "J"; break;
            case 12: rankStr = "Q"; break;
            case 13: rankStr = "K"; break;
            case 14: rankStr = "A"; break;
            default: rankStr = std::to_string(card.rank); break;
        }
        std::cout << card.suit << " " << rankStr << "\n";
    }

    return result;
}