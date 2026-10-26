#pragma once
#include <string>

// Playing card model according to PDF specification
// rank: 2-10, 11 = J, 12 = Q, 13 = K, 14 = A
// suit: 'H' (Hearts), 'D' (Diamonds), 'C' (Clubs), 'S' (Spades)
struct Card {
    int rank;
    char suit;

    bool operator==(const Card& other) const {
        return rank == other.rank && suit == other.suit;
    }

    bool operator<(const Card& other) const {
        if (rank != other.rank) return rank < other.rank;
        return suit < other.suit;
    }

    std::string ToString() const {
        std::string r;
        switch (rank) {
            case 11: r = "J"; break;
            case 12: r = "Q"; break;
            case 13: r = "K"; break;
            case 14: r = "A"; break;
            default: r = std::to_string(rank); break;
        }
        return r + suit;
    }
};
