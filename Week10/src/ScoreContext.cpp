#include "ScoreContext.h"

ScoreContext::ScoreContext(PokerHandType handType, int chips, int mult)
    : m_handType(handType),
      m_chips(chips),
      m_mult(mult),
      m_baseScore(chips * mult),
      m_finalScore(chips * mult) {}

PokerHandType ScoreContext::getHandType() const {
    return m_handType;
}

int ScoreContext::getChips() const {
    return m_chips;
}

int ScoreContext::getMult() const {
    return m_mult;
}

int ScoreContext::getBaseScore() const {
    return m_baseScore;
}

int ScoreContext::getFinalScore() const {
    return m_finalScore;
}

void ScoreContext::setFinalScore(int score) {
    m_finalScore = score;
}

void ScoreContext::multiplyScore(int factor) {
    m_finalScore *= factor;
}

void ScoreContext::addScore(int addition) {
    m_finalScore += addition;
}
