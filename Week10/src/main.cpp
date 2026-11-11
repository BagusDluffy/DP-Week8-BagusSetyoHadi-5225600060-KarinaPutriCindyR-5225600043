#include <iostream>
#include <memory>
#include "HandGenerator.h"
#include "PlayerInput.h"
#include "PokerHandEvaluator.h"
#include "ScoringRule.h"
#include "JokerManager.h"
#include "Joker.h"
#include "HandResolver.h"
#include "GameManager.h"

int main() {
    std::cout << "===========================================\n";
    std::cout << "  Balatro-Like Card Game — Week 10 System\n";
    std::cout << "  (Responsibility Separation Architecture)\n";
    std::cout << "===========================================\n\n";

    // 1. Inisialisasi Scoring Layer
    PokerHandEvaluator evaluator;
    ScoringRule scoringRule;

    // 2. Inisialisasi Effect Layer (Joker System)
    JokerManager jokerManager;
    jokerManager.addJoker(std::make_unique<JokerMult2x>());

    // 3. Inisialisasi HandResolver (Penghubung pipeline scoring)
    HandResolver resolver(&evaluator, &scoringRule, &jokerManager);

    // 4. Inisialisasi Input & Card Generator
    HandGenerator generator;
    PlayerInput input;

    // 5. Inisialisasi Orchestrator (GameManager) dengan Target Score = 50
    GameManager gameManager(&generator, &input, &resolver, 50);

    // 6. Jalankan sesi Blind
    gameManager.runBlindSession();

    return 0;
}
