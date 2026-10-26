#pragma once
#include "IRewardRule.h"

// BasicRewardRule: reward = skor jika menang, 0 jika kalah
class BasicRewardRule : public IRewardRule {
public:
    int earnMoney(bool win, int score) override;
};
