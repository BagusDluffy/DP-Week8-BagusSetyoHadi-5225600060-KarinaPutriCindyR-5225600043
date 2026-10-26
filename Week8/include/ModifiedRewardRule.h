#pragma once
#include "IRewardRule.h"

// ModifiedRewardRule: pada ronde genap reward x2, ronde ganjil reward +2
class ModifiedRewardRule : public IRewardRule {
public:
    int earnMoney(bool win, int score) override;

private:
    int m_round = 0;
};
