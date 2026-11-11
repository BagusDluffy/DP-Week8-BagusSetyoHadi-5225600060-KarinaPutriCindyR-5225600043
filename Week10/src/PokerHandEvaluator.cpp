#include "PokerHandEvaluator.h"
#include "Card.h"
#include "ChosenHand.h"
#include <map>
#include <algorithm>

namespace {
    bool checkFlush(const std::vector<Card>& cards) {
        if (cards.size() < 5) return false;
        char firstSuit = cards[0].suit;
        for (const auto& c : cards) {
            if (c.suit != firstSuit) return false;
        }
        return true;
    }

    bool checkStraight(const std::vector<Card>& cards) {
        if (cards.size() < 5) return false;
        std::vector<int> ranks;
        ranks.reserve(cards.size());
        for (const auto& c : cards) {
            ranks.push_back(c.rank);
        }
        std::sort(ranks.begin(), ranks.end());

        // Check duplicate
        for (size_t i = 1; i < ranks.size(); ++i) {
            if (ranks[i] == ranks[i - 1]) return false;
        }

        // Standard straight
        bool standardStraight = true;
        for (size_t i = 1; i < ranks.size(); ++i) {
            if (ranks[i] != ranks[i - 1] + 1) {
                standardStraight = false;
                break;
            }
        }
        if (standardStraight) return true;

        // Ace-low straight: 2, 3, 4, 5, 14 (A)
        if (ranks == std::vector<int>{ 2, 3, 4, 5, 14 }) {
            return true;
        }

        return false;
    }
}

PokerHandType PokerHandEvaluator::evaluate(const std::vector<Card>& cards) const {
    if (cards.empty()) {
        return PokerHandType::HIGH_CARD;
    }

    std::map<int, int> rankCounts;
    for (const auto& c : cards) {
        rankCounts[c.rank]++;
    }

    bool isFlush = checkFlush(cards);
    bool isStraight = checkStraight(cards);

    // Royal Flush: Straight Flush with 10, J, Q, K, A
    if (isFlush && isStraight) {
        std::vector<int> ranks;
        for (const auto& c : cards) ranks.push_back(c.rank);
        std::sort(ranks.begin(), ranks.end());
        if (ranks == std::vector<int>{ 10, 11, 12, 13, 14 }) {
            return PokerHandType::ROYAL_FLUSH;
        }
        return PokerHandType::STRAIGHT_FLUSH;
    }

    // Four of a kind
    for (const auto& [rank, count] : rankCounts) {
        if (count >= 4) return PokerHandType::FOUR_OF_A_KIND;
    }

    // Full House (3 of a kind + pair)
    bool hasThree = false;
    bool hasTwo = false;
    for (const auto& [rank, count] : rankCounts) {
        if (count == 3) hasThree = true;
        else if (count == 2) hasTwo = true;
    }
    if (hasThree && hasTwo) {
        return PokerHandType::FULL_HOUSE;
    }

    // Flush
    if (isFlush) return PokerHandType::FLUSH;

    // Straight
    if (isStraight) return PokerHandType::STRAIGHT;

    // Three of a kind
    if (hasThree) return PokerHandType::THREE_OF_A_KIND;

    // Two pair / Pair
    int pairs = 0;
    for (const auto& [rank, count] : rankCounts) {
        if (count >= 2) pairs++;
    }
    if (pairs >= 2) return PokerHandType::TWO_PAIR;
    if (pairs == 1) return PokerHandType::PAIR;

    return PokerHandType::HIGH_CARD;
}

PokerHandType PokerHandEvaluator::evaluate(const ChosenHand& chosenHand) const {
    return evaluate(chosenHand.getCards());
}
