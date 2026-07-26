#include "chaser.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
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
    GameBoard::printLine();
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

void ScoreBoard::addUsedScore(ScoreBoard::ScoreType scoreType, std::map<int, int> dices, int score) {
    usedScore_[scoreType] = dices;
    scores_[scoreType] = score;
}

int ScoreBoard::calculateScore(const Dices& dices, ScoreType scoreType) const {
    ScoreList possibleList = getPosibleList(dices);
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

ScoreBoard::ScoreList ScoreBoard::getPosibleList(const Dices& dices) const {
     std::map<Dice, int> frequent = dices.getFrequent();
     ScoreList possibleList;
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
         possibleList[ScoreType::Straight] = {{}};;
     }
     if (evenStraight == 5) {
         possibleList[ScoreType::EvenStraight] = {{}};;
     }

    std::map<int, int> fullHouse; // if this map's size is two, that means fullHouse is posible. First int means number and seㅊond means frequent
    std::map<int, int> choice; // if this map's size is three, that means choice is posible. First int means number and second means frequent
    std::map<int, int> fourDice;
    int choiceTwo = 0;
    int choiceOne = 0;
    int fullHouseTwo = 0;
    int fullHouseThree = 0;
    int fourDiceOne = 0;

    for (const auto& f : frequent) {
        if (f.second == 1) {
             fourDice[f.first.getValue()] = 1;
             choice[f.first.getValue()] = 1;
             choiceOne++;
             fourDiceOne++;
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
             possibleList[ScoreType::ChaseOff] = {{}};
             possibleList[ScoreType::FourDice] = {{static_cast<int>(f.first.getValue()), f.second}};
        }
    }
    if (choice.size() == 3 && choiceOne == 1 && choiceTwo == 2) {
        possibleList[ScoreType::Choice] = choice;
    }
    if (fullHouse.size() == 2 && fullHouseThree == 1 && fullHouseTwo == 1) {
        possibleList[ScoreType::FullHouse] = fullHouse;
    }
    if (fourDice.size() == 2 && fourDiceOne == 1) {
        possibleList[ScoreType::FourDice] = fourDice;
    }

    std::erase_if(possibleList, [&](const auto& item) {
            return usedScore_.contains(item.first);
        });

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

void GameBoard::printLine(){
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
    printLine();
}

void GameBoard::rollSelectedDices() {
    dices_.rollSelectedDices();
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

void GameBoard::printPosibleScores() const{
    std::map<ScoreBoard::ScoreType, std::map<int, int>> list = scoreBorad_.getPosibleList(dices_);

     for (const auto& l : list) {
         std::cout << l.first << ": ";
         std::cout << scoreBorad_.calculateScore(dices_, l.first) << std::endl;
     }
     printLine();
}

ScoreBoard::ScoreList GameBoard::getPosibleScores() const{
     return scoreBorad_.getPosibleList(dices_);
}

void Dices::setDice(std::vector<Dice> dices) {
    dices_ = dices;
}

void GameBoard::setDice(std::vector<Dice> dices) {
    dices_.setDice(dices);
}

void GameBoard::choseScore() {
    std::string scoreTypeStr;
    int score = 0;
    ScoreBoard::ScoreType scoreType;
    ScoreBoard::ScoreList list = scoreBorad_.getPosibleList(dices_);
    std::cout << "plz input a score type that you went to add: ";

    while (true) {
        std::cin >> scoreTypeStr;
        if (scoreTypeStr == "Aces") {
            score = scoreBorad_.calculateScore(dices_, ScoreBoard::ScoreType::Aces);
            scoreType = ScoreBoard::ScoreType::Aces;
        } else if (scoreTypeStr == "TwoBeans") {
            score = scoreBorad_.calculateScore(dices_, ScoreBoard::ScoreType::TwoBeans);
            scoreType = ScoreBoard::ScoreType::TwoBeans;
        } else if (scoreTypeStr == "ThreeBeans") {
            score = scoreBorad_.calculateScore(dices_, ScoreBoard::ScoreType::ThreeBeans);
            scoreType = ScoreBoard::ScoreType::ThreeBeans;
        } else if (scoreTypeStr == "FourBeans") {
            score = scoreBorad_.calculateScore(dices_, ScoreBoard::ScoreType::FourBeans);
            scoreType = ScoreBoard::ScoreType::FourBeans;
        } else if (scoreTypeStr == "FiveBeans") {
            score = scoreBorad_.calculateScore(dices_, ScoreBoard::ScoreType::FiveBeans);
            scoreType = ScoreBoard::ScoreType::FiveBeans;
        } else if (scoreTypeStr == "SixBeans") {
            score = scoreBorad_.calculateScore(dices_, ScoreBoard::ScoreType::SixBeans);
            scoreType = ScoreBoard::ScoreType::SixBeans;
        } else if (scoreTypeStr == "Choice") {
            score = scoreBorad_.calculateScore(dices_, ScoreBoard::ScoreType::Choice);
            scoreType = ScoreBoard::ScoreType::Choice;
        } else if (scoreTypeStr == "FullHouse") {
            score = scoreBorad_.calculateScore(dices_, ScoreBoard::ScoreType::FullHouse);
            scoreType = ScoreBoard::ScoreType::FullHouse;
        } else if (scoreTypeStr == "FourDice") {
            score = scoreBorad_.calculateScore(dices_, ScoreBoard::ScoreType::FourDice);
            scoreType = ScoreBoard::ScoreType::FourDice;
        } else if (scoreTypeStr == "EvenStraight") {
            score = scoreBorad_.calculateScore(dices_, ScoreBoard::ScoreType::EvenStraight);
            scoreType = ScoreBoard::ScoreType::EvenStraight;
        }  else if (scoreTypeStr == "Straight") {
            score = scoreBorad_.calculateScore(dices_, ScoreBoard::ScoreType::Straight);
            scoreType = ScoreBoard::ScoreType::Straight;
        } else if (scoreTypeStr == "ChaseOff") {
            score = scoreBorad_.calculateScore(dices_, ScoreBoard::ScoreType::ChaseOff);
            scoreType = ScoreBoard::ScoreType::ChaseOff;
        } else {
            std::cout << "plz input correct score type" << std::endl;
            continue;
        }
        break;
    }

    scoreBorad_.addUsedScore(scoreType, list[scoreType], score);
    score_ += score;

    std::cout << "you got " << score << "point" << std::endl;
    printLine();
}

void GameBoard::printUsedScore() const {
    std::cout << "Used Score: " << std::endl;
    auto scores = scoreBorad_.getScores();
    for (const auto& u : scoreBorad_.getUsedScore()) {
        std::cout << u.first << ": ";
        for (const auto& d : u.second) {
            std::cout << "{ " << d.first << ": " << d.second << " } ";
        }
        std::cout << ": " << scores[u.first] << std::endl;
    }
    printLine();
}

bool GameBoard::checkGameEnd() const {
    if (scoreBorad_.getScores().size() == 12) {
        std::cout << "game over" << std::endl;
        std::cout << "score: " << score_ << std::endl;
        std::cout << "scores: " << std::endl;
        printUsedScore();
        return true;
    }
    return false;
}

void GameBoard::choseScore(ScoreBoard::ScoreType scoreType) {
    std::string scoreTypeStr;
    int score = 0;
    ScoreBoard::ScoreList list = scoreBorad_.getPosibleList(dices_);
    score = scoreBorad_.calculateScore(dices_, scoreType);

    scoreBorad_.addUsedScore(scoreType, list[scoreType], score);
    score_ += score;
}

const ScoreBoard::ScoreList& ScoreBoard::getUsedScore() const {
    return usedScore_;
}

const std::map<ScoreBoard::ScoreType, int>& ScoreBoard::getScores() const {
    return  scores_;
}

void GameBoard::printPosibleListExtra() const{
    ScoreBoard::ScoreList empty_board;
    empty_board[ScoreBoard::ScoreType::ChaseOff]     = { {}, { {} } };
    empty_board[ScoreBoard::ScoreType::Straight]     = { {}, { {} } };
    empty_board[ScoreBoard::ScoreType::EvenStraight] = { {}, { {} } };
    empty_board[ScoreBoard::ScoreType::FourDice]     = { {}, { {} } };
    empty_board[ScoreBoard::ScoreType::FullHouse]    = { {}, { {} } };
    empty_board[ScoreBoard::ScoreType::Choice]       = { {}, { {} } };
    empty_board[ScoreBoard::ScoreType::SixBeans]     = { {}, { {} } };
    empty_board[ScoreBoard::ScoreType::FiveBeans]    = { {}, { {} } };
    empty_board[ScoreBoard::ScoreType::FourBeans]    = { {}, { {} } };
    empty_board[ScoreBoard::ScoreType::ThreeBeans]   = { {}, { {} } };
    empty_board[ScoreBoard::ScoreType::TwoBeans]     = { {}, { {} } };
    empty_board[ScoreBoard::ScoreType::Aces]         = { {}, { {} } };

    std::erase_if(empty_board, [&](const auto& item) {
            return scoreBorad_.getUsedScore().contains(item.first);
        });
    std::erase_if(empty_board, [&](const auto& item) {
            return scoreBorad_.getPosibleList(dices_).contains(item.first);
        });

    for (const auto& e : empty_board) {
        std::cout << e.first << ": 0" << std::endl;
    }
    printPosibleScores();
}
