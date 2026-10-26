#pragma once
#include <random>
#include <optional>
#include "Hand.h"

class HandGenerator {
public:
    // Default constructor menggunakan std::random_device
    HandGenerator();

    // Constructor dengan fixed seed untuk testing deterministik (sesuai FR-03)
    explicit HandGenerator(unsigned int seed);

    // Menghasilkan hand berisi numCards kartu secara random dari deck standar tanpa duplikasi
    Hand generateHand(size_t numCards = 5);

    // Reset generator dengan seed baru
    void setSeed(unsigned int seed);

private:
    std::mt19937 m_rng;
};
