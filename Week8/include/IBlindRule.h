#pragma once

class IBlindRule {
public:
    virtual ~IBlindRule() = default;
    // Memeriksa apakah score memenuhi target (win condition)
    virtual bool checkBlind(int score) = 0;
};
