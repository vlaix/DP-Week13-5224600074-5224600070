#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include "ChosenHand.h"

Hand ChosenHand::chooseCards(Hand& hand) {
    std::set<int> chosen;

    std::cout << "Pilih 5 kartu (masukkan nomor 1-8, pisahkan spasi): ";

    while (chosen.size() < 5) {
        int input;
        std::cin >> input;

        if (input < 1 || input > 8) {
            std::cout << "Nomor tidak valid, masukkan angka 1-8\n";
            continue;
        }

        if (chosen.count(input)) {
            std::cout << "Kartu " << input << " sudah dipilih\n";
            continue;
        }

        chosen.insert(input);
    }

    Hand result;
    
    // 1. Ambil data dari set dan masukkan ke vector biasa untuk kita balik urutannya
    std::vector<int> urutanTerbalik(chosen.begin(), chosen.end());
    
    // 2. Urutkan nomor pilihan dari yang TERBESAR ke TERKECIL
    std::sort(urutanTerbalik.begin(), urutanTerbalik.end(), std::greater<int>());

    // 3. Proses copy ke hasil tarung SEKALIGUS hapus dari tangan utama
    for (int nomor : urutanTerbalik) {
        int idx = nomor - 1; // Konversi menu 1-8 ke indeks 0-7

        if (idx >= 0 && idx < hand.cards.size()) {
            // A. Masukkan ke hasil untuk dihitung skornya nanti
            result.cards.push_back(hand.cards[idx]);

            // B. HAPUS kartu dari tangan asli pemain detik ini juga!
            hand.cards.erase(hand.cards.begin() + idx);
        }
    }

    std::reverse(result.cards.begin(), result.cards.end());

    std::cout << "===Kartu dipilih===\n";
    for (size_t i = 0; i < result.cards.size(); i++) {
        std::string rankStr;
        switch(result.cards[i].rank) {
            case 11: rankStr = "J"; break;
            case 12: rankStr = "Q"; break;
            case 13: rankStr = "K"; break;
            case 14: rankStr = "A"; break;
            default: rankStr = std::to_string(result.cards[i].rank); break;
        }
        std::cout << i+1 << ". " << result.cards[i].suit << " " << rankStr << "\n";
    }

    return result;
}