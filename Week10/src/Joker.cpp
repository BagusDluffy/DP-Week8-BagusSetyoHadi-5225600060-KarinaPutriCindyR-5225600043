#include "Joker.h"
#include <iostream>

Joker::Joker(std::string name, std::string description)
    : m_name(std::move(name)), m_description(std::move(description)) {}

const std::string& Joker::getName() const {
    return m_name;
}

const std::string& Joker::getDescription() const {
    return m_description;
}

JokerMult2x::JokerMult2x()
    : Joker("Joker Mult x2", "Multiplies score by 2 if base score is at least 20") {}

void JokerMult2x::onScoreCalculated(ScoreContext& context) {
    int baseScore = context.getBaseScore();
    if (baseScore >= 20) {
        int oldFinal = context.getFinalScore();
        context.multiplyScore(2);
        std::cout << "  [JOKER] " << m_name << ": Base score " << baseScore
                  << " >= 20 -> Score multiplied x2 (" << oldFinal
                  << " -> " << context.getFinalScore() << ")\n";
    } else {
        std::cout << "  [JOKER] " << m_name << ": Base score " << baseScore
                  << " < 20 -> Condition not met, score unchanged ("
                  << context.getFinalScore() << ")\n";
    }
}
