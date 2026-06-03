# Balatro Scoring System

> **Technical Design Document** — C++ Design Pattern Implementation

## Overview

Balatro adalah sistem evaluasi dan scoring poker hand berbasis C++ yang terinspirasi dari roguelike game. Sistem ini dirancang secara modular, di mana setiap komponen memiliki tanggung jawab yang jelas dan dapat dikembangkan secara independen.

**Fitur Utama:**
- Evaluasi poker hand menggunakan **Chain of Responsibility Pattern**
- Kalkulasi skor berdasarkan jenis hand
- Efek Joker yang memodifikasi skor
- Blind progression menggunakan **State Pattern**
- Skip reward system menggunakan **Command Pattern**

---

## High-Level Architecture

| System | Responsibility |
|---|---|
| `GameManager` | Mengontrol alur permainan keseluruhan |
| `HandGenerator` | Membuat dan mengacak deck 52 kartu, membagi 8 kartu ke player |
| `HandPlayer` / `ChosenHand` | Player memilih 5 kartu dari 8 kartu yang diberikan |
| `PokerHandChecker` Chain | Mendeteksi jenis poker hand dari kartu yang dipilih |
| `ScoringRule` | Menghitung base score berdasarkan HandRank |
| `JokerManager` | Mengelola dan mengaplikasikan efek joker |
| `ScoreContext` | Menyimpan data skor yang dapat dimodifikasi joker |
| `BlindState` / `GameSession` | Mengelola blind progression menggunakan State Pattern |
| `RewardCommand` | Mengelola skip reward menggunakan Command Pattern |

---

## Runtime Flow

```
main()
└→ GameManager::runSession(gameSession)
    ├→ HandGenerator::generateHand()       // 8 kartu random
    ├→ HandPlayer::playHand(hand)          // player pilih 5 kartu
    ├→ ScoringRule::scoreHand(chosenHand)  // deteksi & hitung skor
    │   └→ PokerHandChecker chain          // Chain of Responsibility
    │       └→ convertRankToScore()        // mapping rank → score
    ├→ JokerManager::applyJokers(context)  // modifikasi skor
    ├→ BlindRule::checkBlind(finalScore)   // menang/kalah
    └→ BlindState::handleNextState()       // pindah ke blind berikutnya
```

---

## Card System

### Card

Representasi satu kartu permainan. Setiap kartu memiliki:

| Field | Tipe & Keterangan |
|---|---|
| `rank` | `int` — nilai 2 sampai 14 (11=J, 12=Q, 13=K, 14=A) |
| `suit` | `char` — H (Heart), D (Diamond), C (Club), S (Spade) |

### Hand

Struct yang menyimpan kumpulan kartu sebagai vector. Digunakan di seluruh sistem mulai dari HandGenerator hingga checker.

| Field | Keterangan |
|---|---|
| `std::vector<Card> cards` | Kumpulan kartu yang dimiliki player |

---

## 🎲 Hand Generator

`HandGenerator` bertanggung jawab membuat deck lengkap, mengacaknya, dan memberikan 8 kartu kepada player.

### Alur `generateHand()`

1. Buat 52 kartu (4 suit × 13 rank, rank 2–14)
2. Shuffle menggunakan `std::mt19937` dengan seed dari `std::time(0)`
3. Ambil 8 kartu teratas dari deck
4. Tampilkan ke player dengan nomor 1–8
5. Return `Hand` berisi 8 kartu

### Konversi Rank

| `int rank` | Tampilan |
|---|---|
| 2 - 10 | Angka |
| 11 | J (Jack) |
| 12 | Q (Queen) |
| 13 | K (King) |
| 14 | A (Ace) |

---

## ChosenHand

`ChosenHand` mengelola proses player memilih 5 kartu dari 8 kartu yang digenerate.

### Proses Pemilihan

- Player melihat 8 kartu bernomor 1–8
- Player input 5 nomor dipisah spasi (contoh: `1 3 5 7 8`)
- Validasi: nomor di luar range 1–8 ditolak
- Validasi: nomor yang sama tidak bisa dipilih dua kali
- 5 kartu yang dipilih dikembalikan sebagai `Hand` baru

> `std::set` digunakan untuk mencegah duplikasi pilihan. `std::cin` membaca input satu per satu sehingga player cukup menekan Enter sekali setelah mengetik semua nomor.

---

## Poker Hand Evaluation — Chain of Responsibility

### `PokerHandChecker` (Abstract Base Class)

Interface kontrak yang harus diimplementasikan semua checker:

| Member | Keterangan |
|---|---|
| `virtual HandRank check(const Hand&) = 0` | Pure virtual — wajib diimplementasi child class |
| `void setNext(PokerHandChecker* next)` | Menyambungkan checker ke checker berikutnya |
| `PokerHandChecker* nextChecker = nullptr` | Pointer ke checker selanjutnya dalam chain |

### Pola Kerja Setiap Checker

Semua checker mengikuti pola yang sama:

```cpp
HandRank XxxChecker::check(const Hand& hand)
{
    if (isXxx(hand))        // cocok?
        return HandRank::XXX;       // ya → selesai
    if (nextChecker)
        return nextChecker->check(hand);  // tidak → lempar ke next
    return HandRank::HIGH_CARD;     // tidak ada next → fallback
}
```

### PokerHelper

Fungsi helper bersama yang dipakai checker yang perlu menghitung frekuensi rank:

```cpp
std::map<int, int> getRankCount(const Hand& hand)
```

Menghasilkan map berisi jumlah kemunculan tiap rank. Contoh untuk hand `{10H, 10D, JH, JD, QH}`:
```
{10:2, 11:2, 12:1}
```

### Urutan Evaluasi & Logika Checker

Chain dimulai dari rank tertinggi untuk memastikan hand dengan rank tinggi tidak salah terdeteksi:

| Prioritas | Checker | Logika Deteksi |
|---|---|---|
| 1 | `FlushFiveChecker` | Semua suit sama + semua rank sama (5 kartu identik) |
| 2 | `FlushHouseChecker` | Semua suit sama + pola Full House (3+2) |
| 3 | `FiveOfAKindChecker` | 1 rank muncul 5 kali |
| 4 | `RoyalFlushChecker` | Suit sama + rank persis {10,J,Q,K,A} |
| 5 | `StraightFlushChecker` | Suit sama + rank berurutan setelah di-sort |
| 6 | `FourOfAKindChecker` | 1 rank muncul 4 kali |
| 7 | `FullHouseChecker` | Ada rank muncul 3x + rank lain muncul 2x |
| 8 | `FlushChecker` | Semua suit sama |
| 9 | `StraightChecker` | Rank berurutan setelah di-sort |
| 10 | `ThreeOfKindChecker` | 1 rank muncul 3x, tidak ada pair |
| 11 | `TwoPairChecker` | Tepat 2 rank yang masing-masing muncul 2x |
| 12 | `PairChecker` | Tepat 1 rank yang muncul 2x |
| 13 | `HIGH_CARD` | Fallback otomatis jika tidak ada yang cocok |

> **Kenapa `HIGH_CARD` tidak perlu checker tersendiri?** Karena setiap checker sudah memiliki `return HandRank::HIGH_CARD` di akhir sebagai fallback. Checker terakhir (`PairChecker`) yang `nextChecker`-nya `nullptr` akan otomatis return `HIGH_CARD` jika tidak ada yang sesuai.

---

## Scoring System

### ScoringRule

`ScoringRule` memiliki dua tanggung jawab yang terpisah:

- **Evaluasi**: mendelegasikan ke chain checker untuk mendapatkan `HandRank`
- **Konversi**: mengubah `HandRank` menjadi nilai score menggunakan `convertRankToScore()`

`ScoringRule` menyimpan semua checker sebagai member variable agar checker tetap hidup selama `ScoringRule` hidup (menghindari dangling pointer). Chain disambungkan di constructor.

### Tabel Score

| HandRank | Base Score |
|---|---|
| `FLUSH_FIVE` | 65 |
| `FLUSH_HOUSE` | 60 |
| `FIVE_OF_A_KIND` | 55 |
| `ROYAL_FLUSH` | 50 |
| `STRAIGHT_FLUSH` | 45 |
| `FOUR_OF_A_KIND` | 40 |
| `FULL_HOUSE` | 35 |
| `FLUSH` | 30 |
| `STRAIGHT` | 25 |
| `THREE_OF_A_KIND` | 20 |
| `TWO_PAIR` | 15 |
| `PAIR` | 10 |
| `HIGH_CARD` | 5 |

---

## Joker System

### Arsitektur

| Class | Tanggung Jawab |
|---|---|
| `JokerObserver` | Interface + struct `ScoreContext` (chips, mult, handRank) |
| `Joker` | Abstract base class — wajib implement `getName()`, `getDescription()`, `onScoreCalculated()` |
| `JokerManager` | Menyimpan dan menjalankan semua joker |
| `ScoreContext` | Data skor mutable yang dimodifikasi joker (chips, mult, handRank) |

### Alur Joker

```
Base score dihitung oleh ScoringRule
    ↓
ScoreContext{chips=baseScore, mult=1, handRank=rank}
    ↓
JokerManager::applyJokers(context)
    ↓
Setiap joker memodifikasi context.chips atau context.mult
    ↓
finalScore = context.chips × context.mult
```

### Built-in Jokers

| Joker | Kondisi Aktif | Efek |
|---|---|---|
| `PairJoker` | `handRank == PAIR` | +4 mult |
| `FlatChipJoker` | Selalu aktif | +20 chips |

### Cara Menambah Joker Baru

```cpp
// 1. Buat class baru yang inherit dari Joker
class MyJoker : public Joker {
    std::string getName() override { ... }
    std::string getDescription() override { ... }
    void onScoreCalculated(ScoreContext& ctx) override { ... }
};

// 2. Daftarkan di GameManager constructor
jokerManager.addJoker(std::make_unique<MyJoker>());
```

---

## Blind System — State Pattern

### Latar Belakang

Blind progression diimplementasikan menggunakan **State Pattern** untuk menghindari `if-else` panjang dan membuat setiap blind memiliki behavior sendiri yang terisolasi.

### `BlindState` Interface

| Fungsi Virtual | Keterangan |
|---|---|
| `getBlindName()` | Nama blind yang ditampilkan ke player |
| `getTargetScore()` | Skor minimum yang harus dicapai untuk menang |
| `getRewardMoney()` | Jumlah uang yang didapat jika menang |
| `handleNextState(GameSession&)` | Logika transisi ke state berikutnya |
| `createSkipRewardCommand()` | Membuat command reward saat blind di-skip |

### Concrete Blind States

| State | Target Score | Reward / Transisi |
|---|---|---|
| `SmallBlindState` | 300 | Reward $3 → pindah ke `BigBlindState` |
| `BigBlindState` | 800 | Reward $4 → pindah ke `BossBlindState` |
| `BossBlindState` | 2000 | Reward $5 → `incrementAnte()` + kembali ke `SmallBlindState` |

### Blind Progression Flow

```
Small Blind → Big Blind → Boss Blind
                                ↓
                           Ante naik (+1)
                                ↓
                        Small Blind (cycle ulang)
```

### GameSession

Menyimpan state runtime permainan:

| Field | Keterangan |
|---|---|
| `currentBlind` | Pointer ke blind state yang aktif saat ini |
| `currentAnte` | Nomor ante saat ini (mulai dari 1) |
| `money` | Total uang yang dimiliki player |
| `pendingCommands` *(planned)* | Queue command reward yang menunggu dieksekusi |

---

## Skip Reward System — Command Pattern

### Konsep

Saat player men-skip sebuah blind, sistem membuat `RewardCommand` yang disimpan di pending queue dan dieksekusi nanti berdasarkan timing tertentu.

```
BlindState → createSkipRewardCommand()
    ↓
PendingCommand disimpan di GameSession
    ↓
executePendingCommands() dipanggil saat timing tepat
    ↓
RewardCommand::execute() memodifikasi GameSession
```

### `RewardCommand` Interface

| Fungsi Virtual | Keterangan |
|---|---|
| `getName()` | Nama command |
| `getDescription()` | Deskripsi efek |
| `execute(GameSession&)` | Logika eksekusi yang memodifikasi state |

### CommandTiming

Setiap command memiliki timing eksekusi:

| Timing | Kapan Dieksekusi |
|---|---|
| `Immediate` | Langsung saat command dibuat |
| `NextBlind` | Di awal blind berikutnya |
| `NextShop` | Saat shop dibuka |
| `NextAnte` | Di awal ante berikutnya |

### Concrete Commands

| Command | Efek | Timing Default |
|---|---|---|
| `BonusHandCommand` | +1 `remainingPlays` (tambah giliran main) | `NextBlind` |
| `FreePlayingCardCommand` | Tambah 1 kartu gratis ke deck | `NextShop` |

### PendingCommand

Wrapper yang membungkus `RewardCommand` dengan informasi timing:

| Field | Keterangan |
|---|---|
| `CommandTiming timing` | Kapan command dieksekusi |
| `bool executed` | Flag agar command tidak dieksekusi dua kali |
| `unique_ptr<RewardCommand> command` | Command yang akan dieksekusi |

---

## 📐 Ringkasan Design Patterns

| Pattern | Digunakan Untuk | Keuntungan |
|---|---|---|
| **Chain of Responsibility** | Evaluasi poker hand (checker chain) | Mudah tambah checker baru tanpa ubah kode lain |
| **State Pattern** | Blind progression | Setiap blind punya behavior sendiri, tidak ada `if-else` panjang |
| **Command Pattern** | Skip reward system | Reward baru cukup buat class baru, deferred execution natural |
| **Observer Pattern** | Joker system (`JokerObserver`) | Joker bisa ditambah/hapus tanpa ubah scoring pipeline |

---

## Extension Guide

### Menambah Joker Baru

```cpp
// 1. Buat class baru
class MyJoker : public Joker { ... };

// 2. Implementasi getName(), getDescription(), onScoreCalculated()

// 3. Daftarkan
jokerManager.addJoker(std::make_unique<MyJoker>());
```

### Menambah Poker Hand Baru

```cpp
// 1. Tambah nilai baru di enum
enum class HandRank { ..., MY_HAND };

// 2. Buat checker baru
class MyChecker : public PokerHandChecker {
    HandRank check(const Hand& hand) override { ... }
};

// 3. Tambah ke chain di ScoringRule constructor

// 4. Tambah case di convertRankToScore()
```

### Menambah Blind Baru

```cpp
// 1. Buat class baru
class MyBlindState : public BlindState { ... };

// 2. Implementasi semua fungsi virtual

// 3. Sambungkan di handleNextState() blind sebelumnya
```

### Menambah Reward Command Baru

```cpp
// 1. Buat class baru
class MyCommand : public RewardCommand {
    std::string getName() override { ... }
    std::string getDescription() override { ... }
    void execute(GameSession& session) override { ... }
};

// 2. Gunakan di createSkipRewardCommand() pada BlindState yang sesuai
```
