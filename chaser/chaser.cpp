#include "chaser.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

void Dice::setRandom() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> dis(1, 6);
    unsigned int dice = dis(gen);

    value_ = dice;
}

unsigned int Dice::getValue() const {
    return value_;
}

void Dice::printValue() const {
    std::cout << value_ << std::endl;
}

void Dices::rollDices() {
    for (auto& d : dices_) {
        d.setRandom();
    }
}

void Dices::rollSelectedDices() {
    std::string select;
    std::vector<char> selectedChar(select.begin(), select.end());
    std::vector<int> selectedInt;
    std::cout << "select index of the dices that you went to change. If you don't went to change, than write no." << std::endl;
    bool wrong = false;
    while (true) {
        selectedInt.clear();
        wrong = false;
        std::cin >> select;
        if (select == "no") {
            return;
        }
        selectedChar.assign(select.begin(), select.end());

        for (const auto& c : selectedChar) {
            auto uc = static_cast<unsigned char>(c);
            if (std::isdigit(uc)) {
                int value = (c - '0');
                if (value > 4) {
                    std::cout << "input went wrong. you can only use 0 ~ 4" << std::endl;
                    wrong = true;
                    break;
                }
                if (std::find(selectedInt.begin(), selectedInt.end(), value) != selectedInt.end()) {
                    std::cout << "you can't input same number" << std::endl;
                    wrong = true;
                    break;
                }
                selectedInt.emplace_back(c - '0'); // char -> int 형변환 법. static cast로 하면 아스키 코드나옴ㅇㅇ
            } else {
                std::cout << "input went wrong. you can only use 0 ~ 4" << std::endl;
                wrong = true;
                break;
            }
        }

        if (!wrong) {
            break;
        }
    }

    for (const auto& i : selectedInt) {
        dices_[i].setRandom();
    }
}

void Dices::printDices() const {
    int index = 0;
    for (const auto& d : dices_) {
        std::cout << index << ": " ;
        d.printValue();
        index++;
    }
}

void Dices::makeDices() {
    for (int i = 0; i < 5; i++) {
        dices_.emplace_back(Dice());
    }
}

void Dices::sortDices() {
    std::sort(dices_.begin(), dices_.end(), [](const Dice& a, const Dice& b) {
        return a < b;
    });
}

std::map<Dice, int> Dices::getFrequent() const{
    std::map<Dice, int> frequent;

    for (const auto& d : dices_) {
        frequent[d] += 1;
    }

    return frequent;
}

int Dices::getFrequentDice(int number) const {
    std::map<Dice, int> r = getFrequent();
    auto value = r.find(Dice(number));
    if (value != r.end()) {
        return value->second;
    }

    return 0;
}

int ScoreBoard::calculateScore(const Dices& dices, ScoreType scoreType) const {
    std::map<ScoreBoard::ScoreType, std::map<int, int>> possibleList = checkPosibleList(dices);
    int result = 0;
    switch (scoreType) {
        case ScoreType::Aces: return dices.getFrequentDice(1);
        case ScoreType::TwoBeans: return dices.getFrequentDice(2) * 2;
        case ScoreType::ThreeBeans: return dices.getFrequentDice(3) * 3;
        case ScoreType::FourBeans: return dices.getFrequentDice(4) * 4;
        case ScoreType::FiveBeans: return dices.getFrequentDice(5) * 5;
        case ScoreType::SixBeans: return dices.getFrequentDice(6) * 6;
        case ScoreType::Choice: {
            if (possibleList.contains(ScoreType::Choice)) {
                for (const auto& p : possibleList[ScoreType::Choice]) {
                    result += p.first * p.second;
                }
                return result;
            }
            break;
        };
        case ScoreType::FullHouse: {
            if (possibleList.contains(ScoreType::FullHouse)) {
                for (const auto& p : possibleList[ScoreType::FullHouse]) {
                    result += p.first * p.second;
                }
                return result;
            }
            break;
        };
        case ScoreType::FourDice: {
            if (possibleList.contains(ScoreType::FourDice)) {
                for (const auto& p : possibleList[ScoreType::FourDice]) {
                    result += p.first * p.second;
                }
                return result;
            }
            break;
        };
        case ScoreType::EvenStraight: {
            if (possibleList.contains(ScoreType::EvenStraight)) {
                return 30;
            }
            break;
        };
        case ScoreType::Straight: {
            if (possibleList.contains(ScoreType::Straight)) {
                return 40;
            }
            break;
        };
        case ScoreType::ChaseOff: {
            if (possibleList.contains(ScoreType::ChaseOff)) {
                return 50;
            }
            break;
        };
    }
    return 0;
}

std::map<ScoreBoard::ScoreType, std::map<int, int>> ScoreBoard::checkPosibleList(const Dices& dices) const {
     std::map<Dice, int> frequent = dices.getFrequent();
     std::map<ScoreType, std::map<int, int>> possibleList;
     int evenStraight = 0; // 5 means evenStraight is complete
     int straight = 0; // 5 means straight is complete

     if (frequent.contains(Dice(1))) {
         possibleList[ScoreType::Aces] = {{1, frequent[Dice(1)]}};
         straight++;
     }
     if (frequent.contains(Dice(2))) {
         possibleList[ScoreType::TwoBeans] = {{2, frequent[Dice(2)]}};
         straight++;
         evenStraight++;
     }
     if (frequent.contains(Dice(3))) {
         possibleList[ScoreType::ThreeBeans] = {{3, frequent[Dice(3)]}};
         straight++;
         evenStraight++;
     }
     if (frequent.contains(Dice(4))) {
         possibleList[ScoreType::FourBeans] = {{4, frequent[Dice(4)]}};
         straight++;
         evenStraight++;
     }
     if (frequent.contains(Dice(5))) {
         possibleList[ScoreType::FiveBeans] = {{5, frequent[Dice(5)]}};
         straight++;
         evenStraight++;
     }
     if (frequent.contains(Dice(6))) {
         possibleList[ScoreType::SixBeans] = {{6, frequent[Dice(6)]}};;
         evenStraight++;
     }

     if (straight == 5) {
         possibleList[ScoreType::Straight] = {{0, 0}};;
     }
     if (evenStraight == 5) {
         possibleList[ScoreType::EvenStraight] = {{0, 0}};;
     }

    std::map<int, int> fullHouse; // if this map's size is two, that means fullHouse is posible. First int means number and seㅊond means frequent
    std::map<int, int> choice; // if this map's size is three, that means choice is posible. First int means number and second means frequent
    std::map<int, int> fourDice;
    int choiceTwo = 0;
    int choiceOne = 0;
    int fullHouseTwo = 0;
    int fullHouseThree = 0;

    for (const auto& f : frequent) {
        if (f.second == 1) {
             fourDice[f.first.getValue()] = 1;
             choice[f.first.getValue()] = 1;
             choiceOne++;
        }
        if (f.second == 2) {
            choice[f.first.getValue()] = 2;
            fullHouse[f.first.getValue()] = 2;
            choiceTwo++;
            fullHouseTwo++;
        }
        if (f.second == 3) {
             fullHouse[f.first.getValue()] = 3;
             fullHouseThree++;
        }
        if (f.second == 4) {
             fourDice[f.first.getValue()] = 4;
        }
        if (f.second == 5) {
             possibleList[ScoreType::ChaseOff] = {{static_cast<int>(f.first.getValue()), f.second}};
             possibleList[ScoreType::FourDice] = {{static_cast<int>(f.first.getValue()), f.second}};
        }
    }
    if (choice.size() == 3 && choiceOne == 1 && choiceTwo == 2) {
        possibleList[ScoreType::Choice] = choice;
    }
    if (fullHouse.size() == 2 && fullHouseThree == 1 && fullHouseTwo == 1) {
        possibleList[ScoreType::FullHouse] = fullHouse;
    }
    if (fourDice.size() == 2) {
        possibleList[ScoreType::FourDice] = fourDice;
    }

     return possibleList;
}

void GameBoard::sortDices() {
    if (autoSort_) {
        dices_.sortDices();
    }
}

void GameBoard::sortPrintDices() {
    if (autoSort_) {
        std::cout << "Sorted ";
        sortDices();
        printDices();
    }
}

void GameBoard::printLine() const {
    std::cout << "--------------------" << std::endl;
}

void GameBoard::printDices() const{
    std::cout << "Dices: " << std::endl;
    dices_.printDices();
    printLine();
}

void GameBoard::rollDices() {
    dices_.rollDices();
}

void GameBoard::makeDices() {
    dices_.makeDices();
}

void GameBoard::pntCalculatedScore(ScoreBoard::ScoreType scoreType) const {
    std::cout << scoreType << "'s score is " << scoreBorad_.calculateScore(dices_, scoreType) << std::endl;
}

void GameBoard::rollSelectedDices() {
    dices_.rollSelectedDices();
}

void GameBoard::checkPosibleList() const {
     std::map<ScoreBoard::ScoreType, std::map<int, int>> possibleList = scoreBorad_.checkPosibleList(dices_);

     for (const auto& p : possibleList) {
         std::cout << p.first << std::endl;
     }
}

void GameBoard::turnAutoSort() {
    std::string answer;
    std::cout << "Auto Sort: yes | no" << std::endl;
    while (true) {
        std::cin >> answer;

        if (answer == "yes") {
            autoSort_ = true;
            break;
        }
        else if (answer == "no") {
            autoSort_ = false;
            break;
        }
        else {
            std::cout << "Answer should be yes or no only. Plz try again." << std::endl;
        }
    }
    printLine();
}

void Dices::setDice(std::vector<Dice> dices) {
    dices_ = dices;
}

void GameBoard::setDice(std::vector<Dice> dices) {
    dices_.setDice(dices);
}
