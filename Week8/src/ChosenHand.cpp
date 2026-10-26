#include "ChosenHand.h"
#include <algorithm>

bool ChosenHand::selectCard(const Card& card, const Hand& availableHand) {
    // 1. Cek apakah kartu memang ada di availableHand
    auto itAvail = std::find(availableHand.cards.begin(), availableHand.cards.end(), card);
    if (itAvail == availableHand.cards.end()) {
        return false; // Kartu tidak tersedia di hand
    }

    // 2. Cek apakah kartu sudah pernah dipilih sebelumnya (mencegah duplikasi pemilihan)
    auto itChosen = std::find(m_selectedCards.begin(), m_selectedCards.end(), card);
    if (itChosen != m_selectedCards.end()) {
        return false; // Sudah dipilih
    }

    m_selectedCards.push_back(card);
    return true;
}

bool ChosenHand::selectCardByIndex(size_t index, const Hand& availableHand) {
    if (index >= availableHand.cards.size()) {
        return false; // Indeks di luar rentang
    }
    return selectCard(availableHand.cards[index], availableHand);
}

void ChosenHand::selectAll(const Hand& availableHand) {
    clear();
    for (const auto& card : availableHand.cards) {
        selectCard(card, availableHand);
    }
}

void ChosenHand::clear() {
    m_selectedCards.clear();
}

const std::vector<Card>& ChosenHand::getCards() const {
    return m_selectedCards;
}

size_t ChosenHand::getCardCount() const {
    return m_selectedCards.size();
}

bool ChosenHand::isEmpty() const {
    return m_selectedCards.empty();
}

Hand ChosenHand::toHand() const {
    Hand h;
    h.cards = m_selectedCards;
    return h;
}
