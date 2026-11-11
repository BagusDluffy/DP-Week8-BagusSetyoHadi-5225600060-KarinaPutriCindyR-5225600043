#pragma once
#include "HandGenerator.h"
#include "PlayerInput.h"
#include "HandResolver.h"

// GameManager: Orchestrator utama alur Blind dan batas maksimal 3 hand
class GameManager {
public:
    GameManager(
        HandGenerator* generator,
        PlayerInput*   input,
        HandResolver*  resolver,
        int targetScore = 50
    );

    bool runBlindSession();

private:
    HandGenerator* m_generator;
    PlayerInput*   m_input;
    HandResolver*  m_resolver;
    int            m_targetScore;
    int            m_accumulatedScore = 0;
};
