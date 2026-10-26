#include "ChainScoringRule.h"
#include <iostream>

ChainScoringRule::ChainScoringRule() {
    // Rangkai chain dari tangan terkuat ke terlemah
    m_flushFive.setNext(&m_flushHouse);
    m_flushHouse.setNext(&m_fiveOfAKind);
    m_fiveOfAKind.setNext(&m_royalFlush);
    m_royalFlush.setNext(&m_straightFlush);
    m_straightFlush.setNext(&m_fourOfAKind);
    m_fourOfAKind.setNext(&m_fullHouse);
    m_fullHouse.setNext(&m_flush);
    m_flush.setNext(&m_straight);
    m_straight.setNext(&m_threeOfAKind);
    m_threeOfAKind.setNext(&m_twoPair);
    m_twoPair.setNext(&m_pair);
    m_pair.setNext(&m_highCard);
    // m_highCard tidak perlu setNext — selalu cocok sebagai fallback
}

int ChainScoringRule::scoreHand(const Hand& hand) {
    if (hand.cards.empty()) {
        std::cout << "[SCORE] Empty hand, score = 0\n";
        return 0;
    }
    std::cout << "Calculating hand score...\n";
    HandRank rank = m_flushFive.check(hand);
    int score = convertRankToScore(rank);
    std::cout << "Final score = " << score << "\n";
    return score;
}

int ChainScoringRule::convertRankToScore(HandRank rank) {
    switch (rank) {
        case HandRank::FLUSH_FIVE:       return 100;
        case HandRank::FLUSH_HOUSE:      return 80;
        case HandRank::FIVE_OF_A_KIND:   return 70;
        case HandRank::ROYAL_FLUSH:      return 60;
        case HandRank::STRAIGHT_FLUSH:   return 50;
        case HandRank::FOUR_OF_A_KIND:   return 40;
        case HandRank::FULL_HOUSE:       return 35;
        case HandRank::FLUSH:            return 30;
        case HandRank::STRAIGHT:         return 25;
        case HandRank::THREE_OF_A_KIND:  return 20;
        case HandRank::TWO_PAIR:         return 15;
        case HandRank::PAIR:             return 10;
        case HandRank::HIGH_CARD:
        default:                         return 5;
    }
}
