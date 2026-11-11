#pragma once

class ScoreContext;

// JokerObserver: Interface observer untuk entitas Joker
class JokerObserver {
public:
    virtual ~JokerObserver() = default;
    virtual void onScoreCalculated(ScoreContext& context) = 0;
};
