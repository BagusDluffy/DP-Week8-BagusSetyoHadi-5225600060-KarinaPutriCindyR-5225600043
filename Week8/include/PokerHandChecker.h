#pragma once
#include "Hand.h"
#include "HandRank.h"

// Abstract handler Chain of Responsibility untuk pengecekan kombinasi kartu poker
class PokerHandChecker {
public:
    virtual ~PokerHandChecker() = default;

    virtual HandRank check(const Hand& hand) = 0;
    void setNext(PokerHandChecker* next);

protected:
    PokerHandChecker* nextChecker = nullptr;
};
