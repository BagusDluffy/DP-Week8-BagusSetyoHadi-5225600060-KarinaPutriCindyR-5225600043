#pragma once
#include <algorithm>
#include <map>
#include <vector>
#include "Hand.h"

namespace PokerUtils {

inline std::map<int, int> countRanks(const Hand& hand) {
    std::map<int, int> counts;
    for (const auto& c : hand.cards) {
        counts[c.rank]++;
    }
    return counts;
}

inline std::map<char, int> countSuits(const Hand& hand) {
    std::map<char, int> counts;
    for (const auto& c : hand.cards) {
        counts[c.suit]++;
    }
    return counts;
}

inline bool isFlush(const Hand& hand) {
    if (hand.cards.size() < 5) return false;
    char s = hand.cards[0].suit;
    for (const auto& c : hand.cards) {
        if (c.suit != s) return false;
    }
    return true;
}

inline bool isStraight(const Hand& hand) {
    if (hand.cards.size() != 5) return false;
    std::vector<int> ranks;
    for (const auto& c : hand.cards) {
        ranks.push_back(c.rank);
    }
    std::sort(ranks.begin(), ranks.end());
    // Hapus duplikat kalau ada
    ranks.erase(std::unique(ranks.begin(), ranks.end()), ranks.end());
    if (ranks.size() != 5) return false;

    // Normal straight (misal 2-3-4-5-6 atau 10-J-Q-K-A)
    if (ranks[4] - ranks[0] == 4) return true;

    // Wheel Straight (A-2-3-4-5 dimana A=14)
    if (ranks == std::vector<int>{2, 3, 4, 5, 14}) return true;

    return false;
}

} // namespace PokerUtils
