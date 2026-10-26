#pragma once
#include "Hand.h"

class IScoringRule {
public:
    virtual ~IScoringRule() = default;
    // Menghitung base score dari hand yang dimainkan
    virtual int scoreHand(const Hand& hand) = 0;
};
