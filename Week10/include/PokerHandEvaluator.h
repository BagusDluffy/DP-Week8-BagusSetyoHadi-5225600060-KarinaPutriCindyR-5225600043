#pragma once
#include <vector>
#include "PokerHandType.h"

struct Card;
class ChosenHand;

// PokerHandEvaluator: Bertanggung jawab mengevaluasi kartu dan menentukan PokerHandType
class PokerHandEvaluator {
public:
    PokerHandType evaluate(const std::vector<Card>& cards) const;
    PokerHandType evaluate(const ChosenHand& chosenHand) const;
};
