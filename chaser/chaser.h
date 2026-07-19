#include <iostream>
#include <vector>
#include <map>

class Dice {
private:
    unsigned int value_ = 0;
};

class Dices {
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
private:
    std::map<ScoreType, int> scoreBoard;
};
