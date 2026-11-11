#pragma once
#include <vector>
#include "Card.h"
#include "Hand.h"

// ChosenHand: Mewakili kartu yang dipilih pemain (1 sampai 5 kartu)
class ChosenHand {
public:
    ChosenHand() = default;

    bool addCard(const Card& card);
    void clear();

    const std::vector<Card>& getCards() const;
    size_t size() const;
    bool isEmpty() const;
    bool isValid() const; // Memastikan 1 <= size <= 5

    Hand toHand() const;

private:
    std::vector<Card> m_cards;
};
