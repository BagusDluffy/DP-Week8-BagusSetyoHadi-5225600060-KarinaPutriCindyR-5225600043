# Week 10 — Balatro-Like Responsibility Separation Architecture

Implementasi sistem card game berbasis C++ yang menerapkan prinsip **Responsibility Separation** (Pemisahan Tanggung Jawab) sesuai materi *Reading and Analyzing Responsibility Separation in a Balatro-Like System*.

Arsitektur ini memastikan bahwa kelas orchestrator (`GameManager`) tidak lagi menangani logika evaluasi kartu, perhitungan skor, maupun efek Joker secara langsung.

---

## 1. Arsitektur 4-Layer

Sistem dibagi menjadi 4 layer utama yang saling independen:

```
+-------------------------------------------------------------+
|                     Orchestration Layer                     |
|           GameManager   <--->   HandResolver                |
+------------------------------+------------------------------+
                               |
        +----------------------+----------------------+
        |                                             |
        v                                             v
+-----------------------+                 +---------------------------+
|     Scoring Layer     |                 |       Effect Layer        |
|  PokerHandEvaluator   |                 |       JokerManager        |
|     ScoringRule       |                 | (owns std::vector<Joker>) |
|    HandScoreTable     |                 |       JokerObserver       |
+-----------+-----------+                 +-------------+-------------+
            |                                           |
            +-------------------+-----------------------+
                                |
                                v
+-------------------------------------------------------------+
|                         Data Layer                          |
|         Card, Hand, ChosenHand, PokerHandType,              |
|                     ScoreContext                            |
+-------------------------------------------------------------+
```

### A. Orchestration Layer
- **`GameManager`**:
  - Mengatur keseluruhan alur sesi Blind dan batas ronde (maksimal 3 hand per Blind).
  - Menginisialisasi deck 52 kartu di awal Blind dan memanggil pembagian 8 kartu.
  - Memanggil `PlayerInput` untuk interaksi pemain.
  - Meneruskan `ChosenHand` ke `HandResolver`.
  - Mengakumulasi skor, mendeteksi kemenangan awal (*early win* saat target tercapai), dan menampilkan hasil akhir Blind.
  - *Tidak melakukan evaluasi kombinasi poker, perhitungan skor, atau efek Joker.*
- **`HandResolver`**:
  - Penghubung (*mediator/bridge*) antara hand yang dipilih pemain dengan pipeline scoring.
  - Menerima `ChosenHand`, memanggil `PokerHandEvaluator::evaluate()` untuk menentukan jenis poker.
  - Memanggil `ScoringRule::calculateScore()` untuk menghitung base score.
  - Memanggil `JokerManager::notifyScoreCalculatedWithLog()` untuk memicu modifikasi skor oleh Joker.
  - Mengembalikan `ScoreContext` yang telah diperbarui.

### B. Scoring Layer
- **`PokerHandEvaluator`**:
  - Bertanggung jawab murni mengevaluasi kombinasi kartu pemain (1 sampai 5 kartu).
  - Menentukan jenis kombinasi `PokerHandType` (ROYAL_FLUSH, STRAIGHT_FLUSH, FOUR_OF_A_KIND, FULL_HOUSE, FLUSH, STRAIGHT, THREE_OF_A_KIND, TWO_PAIR, PAIR, HIGH_CARD).
- **`ScoringRule`**:
  - Menghitung base score berdasarkan `PokerHandType` dengan mengambil konfigurasi Chips dan Mult dari `HandScoreTable`.
  - Mengembalikan objek `ScoreContext`.
  - *Tidak memanggil Joker secara langsung.*
- **`HandScoreTable`**:
  - Memisahkan data scoring dari algoritma perhitungan.
  - Menyimpan konfigurasi Chips dan Mult untuk setiap kombinasi poker:
    - High Card: 5 Chips, 1 Mult (Base: 5)
    - Pair: 10 Chips, 2 Mult (Base: 20)
    - Two Pair: 20 Chips, 2 Mult (Base: 40)
    - Three of a Kind: 30 Chips, 3 Mult (Base: 90)
    - Straight: 30 Chips, 4 Mult (Base: 120)
    - Flush: 35 Chips, 4 Mult (Base: 140)
    - Full House: 40 Chips, 4 Mult (Base: 160)
    - Four of a Kind: 60 Chips, 7 Mult (Base: 420)
    - Straight Flush / Royal Flush: 100 Chips, 8 Mult (Base: 800)

### C. Effect Layer (Observer Pattern)
- **`JokerObserver`**:
  - Interface observer abstrak dengan metode `virtual void onScoreCalculated(ScoreContext& context) = 0;`.
- **`Joker`**:
  - Entity game sekaligus implementasi dari `JokerObserver`.
  - Menyimpan identitas nama dan deskripsi, serta mengimplementasikan efek saat menerima notifikasi.
  - Contoh: `JokerMult2x` yang melipatgandakan skor x2 jika base score >= 20.
- **`JokerManager`**:
  - Bertindak sebagai Subject/Notifier dalam Observer Pattern.
  - Memiliki dan mengelola objek Joker menggunakan ownership `std::vector<std::unique_ptr<Joker>>`.
  - Menyediakan `notifyScoreCalculatedWithLog(ScoreContext& context)` dan `applyJokers(ScoreContext& context)`.
  - Penambahan Joker baru tidak memerlukan perubahan pada `GameManager` maupun `PokerHandEvaluator`.

### D. Data Layer
- **`Card`**: Struct kartu dengan rank (2..14) dan suit ('H', 'D', 'C', 'S').
- **`Hand`**: Struct penampung kartu yang dibagikan (`std::vector<Card>`).
- **`ChosenHand`**: Kelas penampung kartu terpilih oleh pemain dengan validasi (1 s/d 5 kartu, tanpa duplikasi).
- **`PokerHandType`**: Enum kategori kombinasi kartu.
- **`ScoreContext`**: Model data scoring yang menyimpan chips, mult, base score, dan final score yang dapat dimutasi secara aman oleh efek Joker melalui `setFinalScore()`, `multiplyScore()`, atau `addScore()`.

---

## 2. Gameplay Requirements

1. **FR-01 — Random Card Generation & Deck Persistence**:
   - Satu sesi Blind menggunakan satu deck standar 52 kartu acak (`std::shuffle` + `std::mt19937`).
   - Setiap hand dibagikan 8 kartu baru.
   - Kartu yang sudah dibagikan tidak akan muncul kembali dalam sesi Blind yang sama.
2. **FR-02 — Player Card Selection**:
   - Pemain memilih 1 sampai 5 kartu melalui input indeks terminal yang dipisahkan spasi.
   - Sistem memvalidasi input: menolak indeks di luar rentang, input duplikat, dan jika pemain memasukkan lebih dari 5 kartu maka diminta input ulang.
   - Pemain melihat ringkasan kartu terpilih dan memberikan konfirmasi `(Y/N)`.
3. **FR-03 — Hand Limit**:
   - Satu sesi Blind memiliki maksimal 3 hand.
   - Jika akumulasi skor mencapai target score (misal: 50), sesi Blind langsung berakhir menang (**WIN**).
   - Jika setelah hand ke-3 target belum tercapai, sesi berakhir kalah (**LOSE**).
4. **FR-04 — Selected Hand**:
   - Hanya kartu yang dipilih dan dikonfirmasi yang diteruskan ke evaluasi poker dan scoring.

---

## 3. Scoring Pipeline

```text
Player Input (PlayerInput)
     |
     v
ChosenHand (1 - 5 cards)
     |
     v
HandResolver
     |
     v
PokerHandEvaluator
     |
     v
Determine PokerHandType
     |
     v
ScoringRule <---> HandScoreTable (Chips, Mult)
     |
     v
Create ScoreContext (Base Score = Chips * Mult)
     |
     v
JokerManager::notifyScoreCalculatedWithLog(context)
     |
     v
JokerObserver::onScoreCalculated (e.g. JokerMult2x)
     |
     v
context.getFinalScore()
     |
     v
GameManager (Accumulate Score & Check Blind)
```

---

## 4. Cara Compile & Run

Kompilasi dan jalankan secara terpisah dari folder `Week10/`:

```bash
cd Week10

# Kompilasi
g++ -std=c++17 -Wall -Iinclude src/*.cpp -o run.exe

# Jalankan game
./run.exe
```

---

## 5. Pembagian Pengerjaan & Git Workflow

- **Person 1 (Bagus Setyo Hadi)** — Branch `feature/week10-core-gameplay`:
  - `Card.h`, `Hand.h`, `ChosenHand.h`, `ChosenHand.cpp`
  - `HandGenerator.h`, `HandGenerator.cpp`
  - `PlayerInput.h`, `PlayerInput.cpp`
  - `GameManager.h`, `GameManager.cpp`
  - `HandResolver.h`, `HandResolver.cpp`
  - `main.cpp`
- **Person 2 (Karina Putri Cindy R)** — Branch `feature/week10-scoring-joker`:
  - `PokerHandType.h`
  - `PokerHandEvaluator.h`, `PokerHandEvaluator.cpp`
  - `ScoringRule.h`, `ScoringRule.cpp`
  - `HandScoreTable.h`, `HandScoreTable.cpp`
  - `ScoreContext.h`, `ScoreContext.cpp`
  - `JokerObserver.h`, `Joker.h`, `Joker.cpp`
  - `JokerManager.h`, `JokerManager.cpp`
