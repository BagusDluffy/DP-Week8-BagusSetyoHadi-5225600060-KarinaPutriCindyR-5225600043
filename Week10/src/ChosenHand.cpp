#include "ChosenHand.h"
#include <algorithm>

bool ChosenHand::addCard(const Card& card) {
    if (m_cards.size() >= 5) {
        return false;
    }
    // Cegah duplikasi
    if (std::find(m_cards.begin(), m_cards.end(), card) != m_cards.end()) {
        return false;
    }
    m_cards.push_back(card);
    return true;
}

void ChosenHand::clear() {
    m_cards.clear();
}

const std::vector<Card>& ChosenHand::getCards() const {
    return m_cards;
}

size_t ChosenHand::size() const {
    return m_cards.size();
}

bool ChosenHand::isEmpty() const {
    return m_cards.empty();
}

bool ChosenHand::isValid() const {
    return m_cards.size() >= 1 && m_cards.size() <= 5;
}

Hand ChosenHand::toHand() const {
    Hand h;
    h.cards = m_cards;
    return h;
}
