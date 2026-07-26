#include <iostream>
#include <sys/stat.h>
#include <vector>
#include <map>
#include <random>
#include <set>

class Dice {
public:
    void setRandom();
    void printValue() const;
    unsigned int getValue() const;

    Dice(int value) : value_(value) {};
    Dice(){};

    bool operator<(const Dice& other) const {
        return value_ < other.value_;
    }

    bool operator==(const Dice& other) const {
        return value_ == other.value_;
    }

    bool operator>(const Dice& other) const {
        return value_ > other.value_;
    }

    bool operator>=(const Dice& other) const {
        return value_ >= other.value_;
    }

    bool operator<=(const Dice& other) const {
        return value_ <= other.value_;
    }

    bool operator!=(const Dice& other) const {
        return value_ != other.value_;
    }

private:
    unsigned int value_ = 0;
};

class Dices {
public:
    void rollDices();
    void rollSelectedDices();
    void printDices() const;
    void makeDices();
    void sortDices();
    std::map<Dice, int> getFrequent() const;
    int getFrequentDice(int number) const;
    void setDice(std::vector<Dice>);
private:
    std::vector<Dice> dices_;
};


class ScoreBoard {
public:
    enum class ScoreType {
        ChaseOff,     // 다섯 주사위 모두 동일한 눈
        Straight,     // 1,2,3,4,5로 배열된 눈
        EvenStraight, // 2,3,4,5,6으로 배열된 눈
        FourDice,     // 네 주사위가 같은 눈
        FullHouse,    // 세 주사위가 같고 나머지 두 주사위가 또 같은 눈
        Choice,       // 두 주사위씩 같은 눈
        SixBeans,     // 6이 나온 눈만 합산. 최저 0점, 최고 30점
        FiveBeans,    // 5가 나온 눈만 합산. 최저 0점, 최고 25점
        FourBeans,    // 4가 나온 눈만 합산. 최저 0점, 최고 20점
        ThreeBeans,   // 3이 나온 눈만 합산. 최저 0점, 최고 15점
        TwoBeans,     // 2가 나온 눈만 합산. 최저 0점, 최고 10점
        Aces          // 1이 나온 눈만 합산. 최저 0점, 최고 5점
    };
    using ScoreList = std::map<ScoreBoard::ScoreType, std::map<int, int>>; // map<int, int> == map<number, frequent>

    ScoreList getPosibleList(const Dices& dices) const;
    int calculateScore(const Dices& dices, ScoreType scoreType) const;
    bool checkPosible(const Dices& dices, ScoreType scoreType) const;
    void addUsedScore(ScoreBoard::ScoreType scoreType, std::map<int, int> dices, int score);
    const ScoreList& getUsedScore() const;
    const std::map<ScoreBoard::ScoreType, int>& getScores() const;
private:
    ScoreList usedScore_;
    std::map<ScoreBoard::ScoreType, int> scores_;
};

inline std::ostream& operator<<(std::ostream& os, const ScoreBoard::ScoreType& type) {
    switch (type) {
        case ScoreBoard::ScoreType::ChaseOff:     os << "ChaseOff"; break;
        case ScoreBoard::ScoreType::Straight:     os << "Straight"; break;
        case ScoreBoard::ScoreType::EvenStraight: os << "EvenStraight"; break;
        case ScoreBoard::ScoreType::FourDice:     os << "FourDice"; break;
        case ScoreBoard::ScoreType::FullHouse:    os << "FullHouse"; break;
        case ScoreBoard::ScoreType::Choice:       os << "Choice"; break;
        case ScoreBoard::ScoreType::SixBeans:     os << "SixBeans"; break;
        case ScoreBoard::ScoreType::FiveBeans:    os << "FiveBeans"; break;
        case ScoreBoard::ScoreType::FourBeans:    os << "FourBeans"; break;
        case ScoreBoard::ScoreType::ThreeBeans:   os << "ThreeBeans"; break;
        case ScoreBoard::ScoreType::TwoBeans:     os << "TwoBeans"; break;
        case ScoreBoard::ScoreType::Aces:         os << "Aces"; break;
    }
    return os;
}

class GameBoard {
public:
    Dices dices_;
    ScoreBoard scoreBorad_;
    int score_ = 0;

    void turnAutoSort();
    void sortDices();
    void printDices() const;
    void rollDices();
    void makeDices();
    void sortPrintDices();
    static void printLine();
    void rollSelectedDices();
    void pntCalculatedScore(ScoreBoard::ScoreType scoreType) const;
    void setDice(std::vector<Dice>);
    void printPosibleScores() const;
    ScoreBoard::ScoreList getPosibleScores() const;
    void choseScore();
    void printUsedScore() const;
    void choseScore(ScoreBoard::ScoreType scoreType);
    bool checkGameEnd() const;
    void printPosibleListExtra() const;
private:
    bool autoSort_ = true;
};
