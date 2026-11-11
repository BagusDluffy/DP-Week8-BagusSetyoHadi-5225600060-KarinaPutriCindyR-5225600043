#include "HandGenerator.h"
#include <algorithm>
#include <iostream>

HandGenerator::HandGenerator() {
    std::random_device rd;
    m_rng.seed(rd());
    startNewBlindSession();
}

HandGenerator::HandGenerator(unsigned int seed) : m_rng(seed) {
    startNewBlindSession();
}

void HandGenerator::startNewBlindSession() {
    m_deck.clear();
    m_deck.reserve(52);

    const char suits[] = { 'H', 'D', 'C', 'S' };
    for (char s : suits) {
        for (int r = 2; r <= 14; ++r) {
            m_deck.push_back(Card{ r, s });
        }
    }

    std::shuffle(m_deck.begin(), m_deck.end(), m_rng);
    m_dealIndex = 0;
}

Hand HandGenerator::dealHand(size_t numCards) {
    Hand hand;
    size_t available = (m_dealIndex < m_deck.size()) ? (m_deck.size() - m_dealIndex) : 0;
    size_t toDeal = std::min(numCards, available);

    for (size_t i = 0; i < toDeal; ++i) {
        hand.cards.push_back(m_deck[m_dealIndex++]);
    }

    return hand;
}

size_t HandGenerator::getRemainingDeckSize() const {
    return (m_dealIndex < m_deck.size()) ? (m_deck.size() - m_dealIndex) : 0;
}
