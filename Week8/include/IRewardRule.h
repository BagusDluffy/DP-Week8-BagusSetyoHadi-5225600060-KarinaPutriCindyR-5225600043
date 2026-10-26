#pragma once

class IRewardRule {
public:
    virtual ~IRewardRule() = default;
    // Menghitung reward berdasarkan hasil win/lose dan skor
    virtual int earnMoney(bool win, int score) = 0;
};
