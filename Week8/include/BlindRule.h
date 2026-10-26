#pragma once
#include "IBlindRule.h"

// BlindRule: menang jika score >= target
class BlindRule : public IBlindRule {
public:
    explicit BlindRule(int targetScore = 20);
    bool checkBlind(int score) override;
    int getTarget() const;

private:
    int m_target;
};
