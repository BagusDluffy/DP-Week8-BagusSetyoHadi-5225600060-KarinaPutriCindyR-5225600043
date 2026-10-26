#pragma once
#include "IScoringRule.h"
#include "PokerHandChecker.h"
#include "PokerHandCheckers.h"

// ChainScoringRule: evaluasi hand melalui Chain of Responsibility (13 checker)
// lalu mengkonversi HandRank menjadi skor numerik
class ChainScoringRule : public IScoringRule {
public:
    ChainScoringRule();
    ChainScoringRule(const ChainScoringRule&) = delete;
    ChainScoringRule& operator=(const ChainScoringRule&) = delete;

    int scoreHand(const Hand& hand) override;

private:
    int convertRankToScore(HandRank rank);

    // Urutan chain: terkuat dulu
    FlushFiveChecker     m_flushFive;
    FlushHouseChecker    m_flushHouse;
    FiveOfAKindChecker   m_fiveOfAKind;
    RoyalFlushChecker    m_royalFlush;
    StraightFlushChecker m_straightFlush;
    FourOfAKindChecker   m_fourOfAKind;
    FullHouseChecker     m_fullHouse;
    FlushChecker         m_flush;
    StraightChecker      m_straight;
    ThreeOfAKindChecker  m_threeOfAKind;
    TwoPairChecker       m_twoPair;
    PairChecker          m_pair;
    HighCardChecker      m_highCard;
};
