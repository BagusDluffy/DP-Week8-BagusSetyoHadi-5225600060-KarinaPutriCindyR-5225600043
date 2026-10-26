#include "ModifiedRewardRule.h"
#include <iostream>

int ModifiedRewardRule::earnMoney(bool win, int score) {
    std::cout << "Calculating reward...\n";
    if (!win) return 0;
    m_round++;
    if (m_round % 2 == 0) return score * 2;
    return score + 2;
}
