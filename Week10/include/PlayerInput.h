#pragma once
#include <iostream>
#include "Hand.h"
#include "ChosenHand.h"

// PlayerInput: Bertanggung jawab terhadap antarmuka input pemain dan validasi pemilihan kartu
class PlayerInput {
public:
    explicit PlayerInput(std::istream& in = std::cin, std::ostream& out = std::cout);

    // Meminta pemain memilih 1 sampai 5 kartu dari hand yang tersedia
    ChosenHand promptSelection(const Hand& availableHand);

private:
    std::istream& m_in;
    std::ostream& m_out;

    void displayHand(const Hand& hand) const;
};
