#include "ScoringRule.h"
#include <iostream>

ScoreContext ScoringRule::calculateScore(PokerHandType handType) const {
    HandScoreInfo info = HandScoreTable::getScoreInfo(handType);
    ScoreContext context(handType, info.chips, info.mult);

    std::cout << "[SCORING]\n";
    std::cout << "  PokerHandType: " << pokerHandTypeToString(handType) << "\n";
    std::cout << "  Chips: " << info.chips << "\n";
    std::cout << "  Mult: " << info.mult << "\n";
    std::cout << "  Base Score: " << context.getBaseScore() << "\n";

    return context;
}
