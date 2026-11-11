#pragma once
#include <memory>
#include "HandGenerator.h"
#include "ChosenHand.h"
#include "HandPlayer.h"
#include "IScoringRule.h"
#include "IBlindRule.h"
#include "IRewardRule.h"
#include "ShopSystem.h"
#include "ScoreSubject.h"
#include "JokerMult2x.h"

// GameManager: orchestrator utama game loop
// Alur: Generate Hand -> Choose Hand -> Play Hand -> Score -> Observer Notification -> Blind Check -> Reward -> Shop
class GameManager {
public:
    GameManager(
        std::unique_ptr<IScoringRule> scoringRule,
        std::unique_ptr<IBlindRule>   blindRule,
        std::unique_ptr<IRewardRule>  rewardRule
    );

    void attachScoreObserver(ScoreObserver* observer);
    void runSession(int totalRounds = 3);

private:
    HandGenerator m_handGenerator;
    HandPlayer    m_handPlayer;
    ShopSystem    m_shop;

    std::unique_ptr<IScoringRule> m_scoringRule;
    std::unique_ptr<IBlindRule>   m_blindRule;
    std::unique_ptr<IRewardRule>  m_rewardRule;

    ScoreSubject m_scoreSubject;
    JokerMult2x  m_jokerMult2x;

    int m_totalMoney = 0;
};
