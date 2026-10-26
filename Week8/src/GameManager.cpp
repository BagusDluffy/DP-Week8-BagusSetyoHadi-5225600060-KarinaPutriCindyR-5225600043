#include "GameManager.h"
#include <iostream>

GameManager::GameManager(
    std::unique_ptr<IScoringRule> scoringRule,
    std::unique_ptr<IBlindRule>   blindRule,
    std::unique_ptr<IRewardRule>  rewardRule)
    : m_scoringRule(std::move(scoringRule)),
      m_blindRule(std::move(blindRule)),
      m_rewardRule(std::move(rewardRule)) {}

void GameManager::runSession(int totalRounds) {
    std::cout << "=== Run Started ===\n";

    for (int round = 1; round <= totalRounds; ++round) {
        std::cout << "\n--- Round " << round << " ---\n";

        // Step 1: Generate hand dari HandGenerator (random deck)
        Hand hand = m_handGenerator.generateHand();

        // Step 2: Tampilkan kartu yang digenerate
        std::cout << "Cards dealt: ";
        for (const Card& c : hand.cards) {
            std::cout << c.ToString() << " ";
        }
        std::cout << "\n";

        // Step 3: Buat ChosenHand — pemain memilih semua kartu (auto-select)
        ChosenHand chosenHand;
        chosenHand.selectAll(hand);

        std::cout << "Chosen cards: ";
        for (const Card& c : chosenHand.getCards()) {
            std::cout << c.ToString() << " ";
        }
        std::cout << "\n";

        // Step 4: Play hand
        m_handPlayer.playHand();

        // Step 5: Hitung base score dari kartu yang dipilih
        Hand playedHand = chosenHand.toHand();
        int score = m_scoringRule->scoreHand(playedHand);
        std::cout << "[SCORE] base score: " << score << "\n";

        // Step 6: Check win/lose
        bool win = m_blindRule->checkBlind(score);

        // Step 7: Hitung reward
        int reward = m_rewardRule->earnMoney(win, score);
        m_totalMoney += reward;
        std::cout << "Money gained: " << reward << " | Total: " << m_totalMoney << "\n";

        // Step 8: Shop
        m_shop.offerItem(round);
    }

    std::cout << "\n=== Run Ended ===\n";
    std::cout << "Final money: " << m_totalMoney << "\n";
}
