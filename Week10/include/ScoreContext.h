#pragma once
#include "PokerHandType.h"

// ScoreContext: Menyimpan informasi scoring (Chips, Mult, Base Score, Final Score)
// serta menyediakan mekanisme update score oleh efek Joker.
class ScoreContext {
public:
    ScoreContext(PokerHandType handType, int chips, int mult);

    PokerHandType getHandType() const;
    int getChips() const;
    int getMult() const;
    int getBaseScore() const;
    int getFinalScore() const;

    void setFinalScore(int score);
    void multiplyScore(int factor);
    void addScore(int addition);

private:
    PokerHandType m_handType;
    int m_chips;
    int m_mult;
    int m_baseScore;
    int m_finalScore;
};
