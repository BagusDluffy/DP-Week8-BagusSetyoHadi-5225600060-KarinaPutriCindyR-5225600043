#pragma once
#include <vector>
#include <random>
#include "Hand.h"
#include "Card.h"

// HandGenerator: Mengelola deck 52 kartu dan membagikan 8 kartu per hand
// Kartu yang telah dibagikan tidak akan muncul kembali selama sesi Blind yang sama.
class HandGenerator {
public:
    HandGenerator();
    explicit HandGenerator(unsigned int seed);

    // Memulai sesi Blind baru: me-reset dan mengacak ulang 52 kartu
    void startNewBlindSession();

    // Membagikan numCards (default 8) kartu acak dari sisa deck
    Hand dealHand(size_t numCards = 8);

    // Sisa kartu di deck
    size_t getRemainingDeckSize() const;

private:
    std::vector<Card> m_deck;
    size_t m_dealIndex = 0;
    std::mt19937 m_rng;
};
