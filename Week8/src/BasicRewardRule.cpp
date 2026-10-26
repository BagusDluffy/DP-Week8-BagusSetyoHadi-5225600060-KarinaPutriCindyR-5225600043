#include "BasicRewardRule.h"
#include <iostream>

int BasicRewardRule::earnMoney(bool win, int score) {
    std::cout << "Calculating reward...\n";
    if (win) return score;
    return 0;
}
