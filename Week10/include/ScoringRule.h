#pragma once
#include "PokerHandType.h"
#include "ScoreContext.h"
#include "HandScoreTable.h"

// ScoringRule: Menghitung base score berdasarkan PokerHandType dan HandScoreTable
class ScoringRule {
public:
    ScoreContext calculateScore(PokerHandType handType) const;
};
