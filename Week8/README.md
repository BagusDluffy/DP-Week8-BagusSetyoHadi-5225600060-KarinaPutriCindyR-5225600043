# Week 8 — Balatro-Like Card Game (C++)

Implementasi lengkap card game ala Balatro dalam C++, menggabungkan fitur dari Week 1-8:

- **Template Method / Core Loop** (Game Loop tetap, detail bisa diganti)
- **Strategy Pattern** (IScoringRule, IRewardRule, IBlindRule — swappable)
- **Chain of Responsibility** (13 PokerHandChecker untuk evaluasi hand)
- **ChosenHand** (representasi pilihan kartu pemain dengan validasi)
- **Random HandGenerator** (deck 52 kartu, Fisher-Yates shuffle via `<random>`)

---

## Cara Compile & Run

```bash
# Dari dalam folder Week8/
g++ -std=c++17 -Wall -Iinclude src/*.cpp -o run.exe
./run.exe
```

---

## Alur Game (Game Loop)

```
=== Run Started ===
  Loop per ronde:
    1. Generate Hand (HandGenerator — random 5 kartu dari deck 52)
    2. Choose Hand   (ChosenHand — pilih kartu dari hand)
    3. Play Hand     (HandPlayer — memainkan pilihan)
    4. Score Hand    (ChainScoringRule → 13 Checker → HandRank → skor)
    5. Check Blind   (BlindRule — menang jika skor >= target)
    6. Earn Money    (ModifiedRewardRule — reward berdasarkan ronde)
    7. Shop          (ShopSystem — tampilkan tawaran)
=== Run Ended ===
```

---

## Struktur Folder

```
Week8/
├── include/              ← Header files
│   ├── Card.h
│   ├── Hand.h
│   ├── ChosenHand.h
│   ├── HandGenerator.h
│   ├── HandPlayer.h
│   ├── HandRank.h
│   ├── PokerUtils.h
│   ├── PokerHandChecker.h
│   ├── PokerHandCheckers.h
│   ├── IScoringRule.h
│   ├── IBlindRule.h
│   ├── IRewardRule.h
│   ├── ChainScoringRule.h
│   ├── BlindRule.h
│   ├── BasicRewardRule.h
│   ├── ModifiedRewardRule.h
│   ├── ShopSystem.h
│   └── GameManager.h
├── src/                  ← Implementation files
│   ├── main.cpp
│   ├── GameManager.cpp
│   ├── HandGenerator.cpp
│   ├── HandPlayer.cpp
│   ├── ChosenHand.cpp
│   ├── PokerHandChecker.cpp
│   ├── PokerHandCheckers.cpp
│   ├── ChainScoringRule.cpp
│   ├── BlindRule.cpp
│   ├── BasicRewardRule.cpp
│   ├── ModifiedRewardRule.cpp
│   └── ShopSystem.cpp
└── README.md
```

---

## Tabel HandRank & Skor

| Nilai | Hand            | Base Score |
|-------|-----------------|------------|
| 13    | Flush Five      | 100        |
| 12    | Flush House     | 80         |
| 11    | Five of a Kind  | 70         |
| 10    | Royal Flush     | 60         |
| 9     | Straight Flush  | 50         |
| 8     | Four of a Kind  | 40         |
| 7     | Full House      | 35         |
| 6     | Flush           | 30         |
| 5     | Straight        | 25         |
| 4     | Three of a Kind | 20         |
| 3     | Two Pair        | 15         |
| 2     | Pair            | 10         |
| 1     | High Card       | 5          |

---

## Design Pattern yang Digunakan

| Pattern | Kelas |
|---------|-------|
| Strategy | `IScoringRule`, `IBlindRule`, `IRewardRule` |
| Chain of Responsibility | `PokerHandChecker` → 13 concrete checker |
| Template Method (implicit) | `GameManager::runSession()` — urutan fase tetap |

---

## FR-01: ChosenHand

`ChosenHand` memvalidasi bahwa kartu yang dipilih berasal dari `Hand` yang tersedia, mencegah duplikasi, dan dapat dikonversi ke `Hand` untuk proses scoring.

```cpp
ChosenHand chosen;
chosen.selectCard(card, hand);           // pilih per kartu dengan validasi
chosen.selectCardByIndex(0, hand);       // pilih by index
chosen.selectAll(hand);                  // pilih semua
Hand playedHand = chosen.toHand();       // konversi ke Hand
```

## FR-02: Checker Logic

Setiap `PokerHandChecker` menggunakan `PokerUtils` untuk mengevaluasi kombinasi kartu **nyata** (bukan dummy value):

- **Flush Five**: 5 kartu rank sama + suit sama
- **Flush House**: Full House + semua suit sama
- **Five of a Kind**: 5 kartu rank sama (suit boleh beda)
- **Royal Flush**: 10-J-Q-K-A suit sama
- **Straight Flush**: 5 berurutan suit sama
- **Four of a Kind / Full House / Flush / Straight / Three / Two Pair / Pair / High Card**: logika standar poker

## FR-03: Random HandGenerator

`HandGenerator` menggunakan `std::mt19937` (Mersenne Twister) + `std::shuffle` (Fisher-Yates) pada deck 52 kartu. Tidak ada hardcoded hand. Mendukung seed deterministik untuk testing:

```cpp
HandGenerator gen(42);          // seed tetap untuk testing
HandGenerator gen;              // seed dari std::random_device
```

## FR-04: Integrasi GameManager

`GameManager::runSession()` mengalirkan data secara eksplisit:

```
Hand hand = generator.generateHand()
↓
ChosenHand chosen; chosen.selectAll(hand)
↓
handPlayer.playHand()
↓
int score = scoringRule->scoreHand(chosen.toHand())
↓
bool win = blindRule->checkBlind(score)
↓
int reward = rewardRule->earnMoney(win, score)
```

---

## Pembagian Tugas

### 👤 Person 1 (Bagus Setyo Hadi)

**Tanggung jawab: Core Loop, Data Model, HandGenerator, ChosenHand, BlindRule, RewardRule, GameManager**

File yang harus di-push:

| File | Keterangan |
|------|------------|
| `include/Card.h` | Struct kartu dengan rank, suit, ToString() |
| `include/Hand.h` | Struct Hand (vector of Card) |
| `include/ChosenHand.h` | Header class ChosenHand |
| `src/ChosenHand.cpp` | Implementasi ChosenHand + validasi |
| `include/HandGenerator.h` | Header HandGenerator (random, seedable) |
| `src/HandGenerator.cpp` | Implementasi shuffle deck 52 kartu |
| `include/HandPlayer.h` | Header HandPlayer |
| `src/HandPlayer.cpp` | Implementasi HandPlayer::playHand() |
| `include/IBlindRule.h` | Interface BlindRule |
| `include/BlindRule.h` | Header BlindRule (target score) |
| `src/BlindRule.cpp` | Implementasi check win/lose |
| `include/IRewardRule.h` | Interface RewardRule |
| `include/BasicRewardRule.h` | Header BasicRewardRule |
| `src/BasicRewardRule.cpp` | Reward = score jika menang |
| `include/ModifiedRewardRule.h` | Header ModifiedRewardRule |
| `src/ModifiedRewardRule.cpp` | Reward x2 di ronde genap, +2 di ganjil |
| `include/ShopSystem.h` | Header ShopSystem |
| `src/ShopSystem.cpp` | Tampilkan tawaran shop |
| `include/GameManager.h` | Header GameManager (orchestrator) |
| `src/GameManager.cpp` | Implementasi runSession() — game loop penuh |
| `src/main.cpp` | Entry point + dependency injection |
| `README.md` | Dokumentasi project |

---

### 👤 Person 2 (Karina Putri Cindy R)

**Tanggung jawab: Chain of Responsibility (13 Checker), Scoring Rule, HandRank, PokerUtils**

File yang harus di-push:

| File | Keterangan |
|------|------------|
| `include/HandRank.h` | Enum 13 jenis hand + HandRankToString() |
| `include/PokerUtils.h` | Helper functions (countRanks, isFlush, isStraight) |
| `include/PokerHandChecker.h` | Abstract base class Chain of Responsibility |
| `src/PokerHandChecker.cpp` | Implementasi setNext() |
| `include/PokerHandCheckers.h` | Header 13 concrete checker dalam satu file |
| `src/PokerHandCheckers.cpp` | Implementasi logic nyata tiap checker |
| `include/IScoringRule.h` | Interface IScoringRule |
| `include/ChainScoringRule.h` | Header ChainScoringRule (merakit 13 checker) |
| `src/ChainScoringRule.cpp` | Merangkai chain + konversi HandRank → skor |

---

## Contoh Output

```
=== Run Started ===

--- Round 1 ---
Generating hand (5 cards)...
Cards dealt: KH 7D 3S AH 7C
Chosen cards: KH 7D 3S AH 7C
Player plays the selected hand...
Calculating hand score...
[CHECK] Detected PAIR
Final score = 10
[SCORE] base score: 10
Checking blind requirement (target: 20)...
Result: LOSE
Calculating reward...
Money gained: 0 | Total: 0
[SHOP] Round 1 — offered: Bonus(+2) cost 2
[SHOP] (skipped)

...

=== Run Ended ===
Final money: ...
```

---

## Reflection

**Chain of Responsibility** memisahkan setiap aturan pengecekan hand ke dalam kelas tersendiri. Checker tidak perlu tahu siapa handler berikutnya, cukup meneruskan jika tidak cocok.

**Strategy Pattern** memungkinkan `GameManager` mengganti `ScoringRule`, `BlindRule`, dan `RewardRule` tanpa mengubah alur game loop.

**ChosenHand** sebagai representasi terpisah dari `Hand` memastikan data hand asli tidak dimodifikasi saat pemain memilih kartu.
