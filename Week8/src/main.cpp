#include <memory>
#include "GameManager.h"
#include "ChainScoringRule.h"
#include "BlindRule.h"
#include "ModifiedRewardRule.h"

int main() {
    // Wiring dependency injection
    GameManager gm(
        std::make_unique<ChainScoringRule>(),
        std::make_unique<BlindRule>(20),      // target skor minimal 20 untuk menang
        std::make_unique<ModifiedRewardRule>()
    );

    gm.runSession(3);
    return 0;
}
