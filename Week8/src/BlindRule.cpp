#include "BlindRule.h"
#include <iostream>

BlindRule::BlindRule(int targetScore) : m_target(targetScore) {}

bool BlindRule::checkBlind(int score) {
    std::cout << "Checking blind requirement (target: " << m_target << ")...\n";
    if (score >= m_target) {
        std::cout << "Result: WIN\n";
        return true;
    }
    std::cout << "Result: LOSE\n";
    return false;
}

int BlindRule::getTarget() const {
    return m_target;
}
