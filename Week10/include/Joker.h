#pragma once
#include <string>
#include "JokerObserver.h"
#include "ScoreContext.h"

// Joker: Abstract game entity yang mengimplementasikan JokerObserver
class Joker : public JokerObserver {
public:
    Joker(std::string name, std::string description);
    virtual ~Joker() = default;

    const std::string& getName() const;
    const std::string& getDescription() const;

    void onScoreCalculated(ScoreContext& context) override = 0;

protected:
    std::string m_name;
    std::string m_description;
};

// JokerMult2x: Jika base score >= 20, kalikan skor dengan 2
class JokerMult2x : public Joker {
public:
    JokerMult2x();
    void onScoreCalculated(ScoreContext& context) override;
};
