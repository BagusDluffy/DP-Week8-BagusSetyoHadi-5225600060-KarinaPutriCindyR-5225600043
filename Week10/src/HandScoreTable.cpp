#include "HandScoreTable.h"

HandScoreInfo HandScoreTable::getScoreInfo(PokerHandType type) {
    switch (type) {
        case PokerHandType::ROYAL_FLUSH:     return { 100, 8 };
        case PokerHandType::STRAIGHT_FLUSH:  return { 100, 8 };
        case PokerHandType::FOUR_OF_A_KIND:  return { 60,  7 };
        case PokerHandType::FULL_HOUSE:      return { 40,  4 };
        case PokerHandType::FLUSH:           return { 35,  4 };
        case PokerHandType::STRAIGHT:        return { 30,  4 };
        case PokerHandType::THREE_OF_A_KIND: return { 30,  3 };
        case PokerHandType::TWO_PAIR:        return { 20,  2 };
        case PokerHandType::PAIR:            return { 10,  2 };
        case PokerHandType::HIGH_CARD:
        default:                             return { 5,   1 };
    }
}
