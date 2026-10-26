#pragma once
#include "PokerHandChecker.h"

// 1. Flush Five: 5 kartu dengan rank yang sama dan suit yang sama
class FlushFiveChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};

// 2. Flush House: Full House (3 rank A + 2 rank B) dan kelimanya suit sama
class FlushHouseChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};

// 3. Five of a Kind: 5 kartu dengan rank yang sama
class FiveOfAKindChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};

// 4. Royal Flush: 10, J, Q, K, A dari suit yang sama
class RoyalFlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};

// 5. Straight Flush: 5 kartu berurutan dari suit yang sama
class StraightFlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};

// 6. Four of a Kind: 4 kartu rank sama
class FourOfAKindChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};

// 7. Full House: 3 kartu rank A + 2 kartu rank B
class FullHouseChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};

// 8. Flush: 5 kartu dari suit yang sama
class FlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};

// 9. Straight: 5 kartu berurutan
class StraightChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};

// 10. Three of a Kind: 3 kartu rank sama
class ThreeOfAKindChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};

// 11. Two Pair: 2 kartu rank A + 2 kartu rank B
class TwoPairChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};

// 12. Pair: 2 kartu rank sama
class PairChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};

// 13. High Card: fallback/selalu cocok jika ada kartu
class HighCardChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};
