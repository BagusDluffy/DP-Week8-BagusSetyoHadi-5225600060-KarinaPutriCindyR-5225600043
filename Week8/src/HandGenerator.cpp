#include "HandGenerator.h"
#include <iostream>
#include <algorithm>
#include <vector>

HandGenerator::HandGenerator() {
    std::random_device rd;
    m_rng.seed(rd());
}

HandGenerator::HandGenerator(unsigned int seed) : m_rng(seed) {}

void HandGenerator::setSeed(unsigned int seed) {
    m_rng.seed(seed);
}

Hand HandGenerator::generateHand(size_t numCards) {
    std::cout << "Generating hand (" << numCards << " cards)...\n";

    // Siapkan standard 52-card deck: 13 ranks (2-14) x 4 suits ('H', 'D', 'C', 'S')
    const char suits[] = { 'H', 'D', 'C', 'S' };
    std::vector<Card> deck;
    deck.reserve(52);

    for (char s : suits) {
        for (int r = 2; r <= 14; ++r) {
            deck.push_back(Card{ r, s });
        }
    }

    // Acak deck menggunakan Fisher-Yates shuffle dengan std::mt19937
    std::shuffle(deck.begin(), deck.end(), m_rng);

    // Ambil sejumlah numCards (maksimal 52)
    size_t takeCount = std::min(numCards, deck.size());
    Hand hand;
    hand.cards.assign(deck.begin(), deck.begin() + takeCount);

    return hand;
}
