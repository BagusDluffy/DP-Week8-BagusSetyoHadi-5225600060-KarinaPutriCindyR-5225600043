#include "PokerHandCheckers.h"
#include "PokerUtils.h"
#include <iostream>
#include <algorithm>

// 1. Flush Five
HandRank FlushFiveChecker::check(const Hand& hand) {
    if (hand.cards.size() == 5 && PokerUtils::isFlush(hand)) {
        auto rc = PokerUtils::countRanks(hand);
        if (rc.size() == 1 && rc.begin()->second == 5) {
            std::cout << "[CHECK] Detected FLUSH FIVE\n";
            return HandRank::FLUSH_FIVE;
        }
    }
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}

// 2. Flush House
HandRank FlushHouseChecker::check(const Hand& hand) {
    if (hand.cards.size() == 5 && PokerUtils::isFlush(hand)) {
        auto rc = PokerUtils::countRanks(hand);
        if (rc.size() == 2) {
            auto it = rc.begin();
            int c1 = it->second;
            ++it;
            int c2 = it->second;
            if ((c1 == 3 && c2 == 2) || (c1 == 2 && c2 == 3)) {
                std::cout << "[CHECK] Detected FLUSH HOUSE\n";
                return HandRank::FLUSH_HOUSE;
            }
        }
    }
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}

// 3. Five of a Kind
HandRank FiveOfAKindChecker::check(const Hand& hand) {
    if (hand.cards.size() == 5) {
        auto rc = PokerUtils::countRanks(hand);
        if (rc.size() == 1 && rc.begin()->second == 5) {
            std::cout << "[CHECK] Detected FIVE OF A KIND\n";
            return HandRank::FIVE_OF_A_KIND;
        }
    }
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}

// 4. Royal Flush
HandRank RoyalFlushChecker::check(const Hand& hand) {
    if (hand.cards.size() == 5 && PokerUtils::isFlush(hand)) {
        std::vector<int> ranks;
        for (const auto& c : hand.cards) ranks.push_back(c.rank);
        std::sort(ranks.begin(), ranks.end());
        if (ranks == std::vector<int>{10, 11, 12, 13, 14}) {
            std::cout << "[CHECK] Detected ROYAL FLUSH\n";
            return HandRank::ROYAL_FLUSH;
        }
    }
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}

// 5. Straight Flush
HandRank StraightFlushChecker::check(const Hand& hand) {
    if (hand.cards.size() == 5 && PokerUtils::isFlush(hand) && PokerUtils::isStraight(hand)) {
        std::cout << "[CHECK] Detected STRAIGHT FLUSH\n";
        return HandRank::STRAIGHT_FLUSH;
    }
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}

// 6. Four of a Kind
HandRank FourOfAKindChecker::check(const Hand& hand) {
    auto rc = PokerUtils::countRanks(hand);
    for (const auto& pair : rc) {
        if (pair.second >= 4) {
            std::cout << "[CHECK] Detected FOUR OF A KIND\n";
            return HandRank::FOUR_OF_A_KIND;
        }
    }
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}

// 7. Full House
HandRank FullHouseChecker::check(const Hand& hand) {
    auto rc = PokerUtils::countRanks(hand);
    bool hasThree = false;
    bool hasTwo = false;
    for (const auto& pair : rc) {
        if (pair.second == 3) {
            hasThree = true;
        } else if (pair.second == 2) {
            hasTwo = true;
        }
    }
    if (hasThree && hasTwo) {
        std::cout << "[CHECK] Detected FULL HOUSE\n";
        return HandRank::FULL_HOUSE;
    }
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}

// 8. Flush
HandRank FlushChecker::check(const Hand& hand) {
    if (PokerUtils::isFlush(hand)) {
        std::cout << "[CHECK] Detected FLUSH\n";
        return HandRank::FLUSH;
    }
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}

// 9. Straight
HandRank StraightChecker::check(const Hand& hand) {
    if (PokerUtils::isStraight(hand)) {
        std::cout << "[CHECK] Detected STRAIGHT\n";
        return HandRank::STRAIGHT;
    }
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}

// 10. Three of a Kind
HandRank ThreeOfAKindChecker::check(const Hand& hand) {
    auto rc = PokerUtils::countRanks(hand);
    for (const auto& pair : rc) {
        if (pair.second >= 3) {
            std::cout << "[CHECK] Detected THREE OF A KIND\n";
            return HandRank::THREE_OF_A_KIND;
        }
    }
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}

// 11. Two Pair
HandRank TwoPairChecker::check(const Hand& hand) {
    auto rc = PokerUtils::countRanks(hand);
    int pairs = 0;
    for (const auto& pair : rc) {
        if (pair.second >= 2) {
            pairs++;
        }
    }
    if (pairs >= 2) {
        std::cout << "[CHECK] Detected TWO PAIR\n";
        return HandRank::TWO_PAIR;
    }
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}

// 12. Pair
HandRank PairChecker::check(const Hand& hand) {
    auto rc = PokerUtils::countRanks(hand);
    for (const auto& pair : rc) {
        if (pair.second >= 2) {
            std::cout << "[CHECK] Detected PAIR\n";
            return HandRank::PAIR;
        }
    }
    return nextChecker ? nextChecker->check(hand) : HandRank::HIGH_CARD;
}

// 13. High Card
HandRank HighCardChecker::check(const Hand& hand) {
    (void)hand;
    std::cout << "[CHECK] Detected HIGH CARD\n";
    return HandRank::HIGH_CARD;
}
