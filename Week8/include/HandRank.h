#pragma once
#include <string>

enum class HandRank {
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH,
    FIVE_OF_A_KIND,
    FLUSH_HOUSE,
    FLUSH_FIVE
};

inline std::string HandRankToString(HandRank rank) {
    switch (rank) {
        case HandRank::HIGH_CARD:       return "HIGH CARD";
        case HandRank::PAIR:            return "PAIR";
        case HandRank::TWO_PAIR:        return "TWO PAIR";
        case HandRank::THREE_OF_A_KIND: return "THREE OF A KIND";
        case HandRank::STRAIGHT:        return "STRAIGHT";
        case HandRank::FLUSH:           return "FLUSH";
        case HandRank::FULL_HOUSE:      return "FULL HOUSE";
        case HandRank::FOUR_OF_A_KIND:  return "FOUR OF A KIND";
        case HandRank::STRAIGHT_FLUSH:  return "STRAIGHT FLUSH";
        case HandRank::ROYAL_FLUSH:     return "ROYAL FLUSH";
        case HandRank::FIVE_OF_A_KIND:  return "FIVE OF A KIND";
        case HandRank::FLUSH_HOUSE:     return "FLUSH HOUSE";
        case HandRank::FLUSH_FIVE:      return "FLUSH FIVE";
        default:                        return "UNKNOWN";
    }
}
