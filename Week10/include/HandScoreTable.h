#pragma once
#include "PokerHandType.h"

struct HandScoreInfo {
    int chips;
    int mult;
};

// HandScoreTable: Menyimpan konfigurasi Chips dan Mult untuk setiap kombinasi poker
class HandScoreTable {
public:
    static HandScoreInfo getScoreInfo(PokerHandType type);
};
