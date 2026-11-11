#include "JokerManager.h"
#include <iostream>

void JokerManager::addJoker(std::unique_ptr<Joker> joker) {
    if (joker) {
        m_jokers.push_back(std::move(joker));
    }
}

void JokerManager::applyJokers(ScoreContext& context) {
    for (auto& joker : m_jokers) {
        if (joker) {
            joker->onScoreCalculated(context);
        }
    }
}

void JokerManager::notifyScoreCalculatedWithLog(ScoreContext& context) {
    std::cout << "[EFFECT]\n";
    if (m_jokers.empty()) {
        std::cout << "  No Jokers equipped.\n";
        return;
    }
    std::cout << "  JokerManager notifying observers (" << m_jokers.size() << " Joker(s))...\n";
    applyJokers(context);
}

const std::vector<std::unique_ptr<Joker>>& JokerManager::getJokers() const {
    return m_jokers;
}

size_t JokerManager::getJokerCount() const {
    return m_jokers.size();
}
