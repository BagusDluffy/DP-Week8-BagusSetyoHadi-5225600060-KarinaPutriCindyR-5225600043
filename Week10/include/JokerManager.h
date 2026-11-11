#pragma once
#include <vector>
#include <memory>
#include "Joker.h"
#include "ScoreContext.h"

// JokerManager: Mengelola kepemilikan Joker dan bertindak sebagai Subject/Notifier.
class JokerManager {
public:
    JokerManager() = default;

    void addJoker(std::unique_ptr<Joker> joker);
    void applyJokers(ScoreContext& context);
    void notifyScoreCalculatedWithLog(ScoreContext& context);

    const std::vector<std::unique_ptr<Joker>>& getJokers() const;
    size_t getJokerCount() const;

private:
    std::vector<std::unique_ptr<Joker>> m_jokers;
};
