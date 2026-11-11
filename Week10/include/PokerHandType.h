#pragma once
#include <string>

enum class PokerHandType {
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH
};

inline std::string pokerHandTypeToString(PokerHandType type) {
    switch (type) {
        case PokerHandType::HIGH_CARD:       return "HIGH CARD";
        case PokerHandType::PAIR:            return "PAIR";
        case PokerHandType::TWO_PAIR:        return "TWO PAIR";
        case PokerHandType::THREE_OF_A_KIND: return "THREE OF A KIND";
        case PokerHandType::STRAIGHT:        return "STRAIGHT";
        case PokerHandType::FLUSH:           return "FLUSH";
        case PokerHandType::FULL_HOUSE:      return "FULL HOUSE";
        case PokerHandType::FOUR_OF_A_KIND:  return "FOUR OF A KIND";
        case PokerHandType::STRAIGHT_FLUSH:  return "STRAIGHT FLUSH";
        case PokerHandType::ROYAL_FLUSH:     return "ROYAL FLUSH";
        default:                             return "UNKNOWN";
    }
}
