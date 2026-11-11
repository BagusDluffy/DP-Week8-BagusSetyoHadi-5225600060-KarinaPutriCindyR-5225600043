#include "HandResolver.h"
#include <iostream>

HandResolver::HandResolver(
    PokerHandEvaluator* evaluator,
    ScoringRule* scoringRule,
    JokerManager* jokerManager)
    : m_evaluator(evaluator),
      m_scoringRule(scoringRule),
      m_jokerManager(jokerManager) {}

ScoreContext HandResolver::resolveHand(const ChosenHand& chosenHand) {
    // 1. Evaluasi jenis poker hand
    PokerHandType handType = m_evaluator->evaluate(chosenHand);

    // 2. Hitung base score via ScoringRule & HandScoreTable
    ScoreContext context = m_scoringRule->calculateScore(handType);

    // 3. Notifikasi Joker observers melalui JokerManager
    if (m_jokerManager) {
        m_jokerManager->notifyScoreCalculatedWithLog(context);
    }

    return context;
}
