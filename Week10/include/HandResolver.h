#pragma once
#include <memory>
#include "ChosenHand.h"
#include "ScoreContext.h"
#include "PokerHandEvaluator.h"
#include "ScoringRule.h"
#include "JokerManager.h"

// HandResolver: Penghubung antara input hand, evaluasi poker, dan scoring pipeline
class HandResolver {
public:
    HandResolver(
        PokerHandEvaluator* evaluator,
        ScoringRule* scoringRule,
        JokerManager* jokerManager
    );

    ScoreContext resolveHand(const ChosenHand& chosenHand);

private:
    PokerHandEvaluator* m_evaluator;
    ScoringRule*        m_scoringRule;
    JokerManager*       m_jokerManager;
};
