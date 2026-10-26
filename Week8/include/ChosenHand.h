#pragma once
#include <vector>
#include "Card.h"
#include "Hand.h"

class ChosenHand {
public:
    ChosenHand() = default;

    // Menambahkan kartu ke pilihan dengan validasi terhadap hand yang tersedia
    bool selectCard(const Card& card, const Hand& availableHand);

    // Menambahkan kartu berdasarkan indeks pada hand yang tersedia
    bool selectCardByIndex(size_t index, const Hand& availableHand);

    // Memilih seluruh kartu dari hand (misal jika memainkan semua kartu)
    void selectAll(const Hand& availableHand);

    // Mengosongkan pilihan
    void clear();

    // Getter kartu terpilih
    const std::vector<Card>& getCards() const;
    size_t getCardCount() const;
    bool isEmpty() const;

    // Konversi menjadi Hand struct untuk diproses oleh scoring rule
    Hand toHand() const;

private:
    std::vector<Card> m_selectedCards;
};
