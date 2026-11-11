#include "GameManager.h"
#include <iostream>

GameManager::GameManager(
    HandGenerator* generator,
    PlayerInput*   input,
    HandResolver*  resolver,
    int targetScore)
    : m_generator(generator),
      m_input(input),
      m_resolver(resolver),
      m_targetScore(targetScore),
      m_accumulatedScore(0) {}

bool GameManager::runBlindSession() {
    std::cout << "================================\n";
    std::cout << "===      BLIND STARTED       ===\n";
    std::cout << "================================\n";
    std::cout << "Target Score: " << m_targetScore << "\n";
    std::cout << "Max Hands: 3\n\n";

    // Inisialisasi satu deck 52 kartu untuk seluruh sesi Blind ini
    m_generator->startNewBlindSession();
    m_accumulatedScore = 0;

    bool won = false;
    const int maxHands = 3;

    for (int handNum = 1; handNum <= maxHands; ++handNum) {
        std::cout << "\n--------------------------------\n";
        std::cout << "---          HAND " << handNum << "          ---\n";
        std::cout << "--------------------------------\n\n";

        // Step 1: Bagikan 8 kartu baru dari deck yang tersisa
        Hand dealtHand = m_generator->dealHand(8);
        std::cout << "[INPUT]\n";
        std::cout << "  8 cards dealt from deck (Remaining in deck: "
                  << m_generator->getRemainingDeckSize() << ").\n\n";

        // Step 2: Dapatkan input kartu dari pemain (1 s/d 5 kartu)
        ChosenHand chosenHand = m_input->promptSelection(dealtHand);

        // Step 3: Tampilkan ChosenHand
        std::cout << "[CHOSEN HAND]\n  ";
        for (const auto& c : chosenHand.getCards()) {
            std::cout << c.toString() << " ";
        }
        std::cout << "\n\n";

        // Step 4: Selesaikan hand melalui HandResolver (Scoring pipeline)
        ScoreContext context = m_resolver->resolveHand(chosenHand);

        // Step 5: Tampilkan Final Score dari hand ini
        int handScore = context.getFinalScore();
        m_accumulatedScore += handScore;

        std::cout << "\n[FINAL SCORE]\n";
        std::cout << "  Hand Score: " << handScore << "\n";
        std::cout << "\n[BLIND]\n";
        std::cout << "  Accumulated Score: " << m_accumulatedScore
                  << " / " << m_targetScore << "\n";

        // Step 6: Cek apakah target skor tercapai
        if (m_accumulatedScore >= m_targetScore) {
            std::cout << "\nTarget score reached early on Hand " << handNum << "!\n";
            won = true;
            break;
        }

        if (handNum < maxHands) {
            std::cout << "\nTarget not yet reached. Continuing to next hand...\n";
        }
    }

    // Step 7: Hasil akhir Blind
    std::cout << "\n================================\n";
    std::cout << "===       BLIND ENDED        ===\n";
    std::cout << "================================\n";
    std::cout << "Final Blind Score: " << m_accumulatedScore << " / " << m_targetScore << "\n";
    std::cout << "Result: " << (won ? "WIN" : "LOSE") << "\n";
    std::cout << "================================\n\n";

    return won;
}
