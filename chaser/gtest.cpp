#include <gtest/gtest.h>
#include "chaser.h"

TEST(SampleTest, addNumber) {
    EXPECT_EQ(3, 1 + 2);
}

TEST(Chaser, calScore) {
    GameBoard game;
    game.makeDices();

    game.setDice({Dice(3), Dice(6), Dice(6), Dice(1), Dice(1)});
    EXPECT_EQ(2, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::Aces));
    ScoreBoard::ScoreList list = {
            {ScoreBoard::ScoreType::ThreeBeans, { {3, 1} }},
            {ScoreBoard::ScoreType::Choice, { {1, 2}, {3, 1}, {6, 2} }},
            {ScoreBoard::ScoreType::SixBeans, { {6, 2} }},
            {ScoreBoard::ScoreType::Aces, { {1, 2} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(2), Dice(2), Dice(6), Dice(2), Dice(1)});
    EXPECT_EQ(6, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::TwoBeans));
    list = {
            {ScoreBoard::ScoreType::TwoBeans, { {2, 3} }},
            {ScoreBoard::ScoreType::SixBeans, { {6, 1} }},
            {ScoreBoard::ScoreType::Aces, { {1, 1} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(2), Dice(2), Dice(6), Dice(2), Dice(3)});
    EXPECT_EQ(3, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::ThreeBeans));
    list = {
            {ScoreBoard::ScoreType::TwoBeans, { {2, 3} }},
            {ScoreBoard::ScoreType::ThreeBeans, { {3, 1} }},
            {ScoreBoard::ScoreType::SixBeans, { {6, 1} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(4), Dice(4), Dice(4), Dice(4), Dice(4)});
    EXPECT_EQ(20, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::FourBeans));
    list = {
            {ScoreBoard::ScoreType::FourBeans, { {4, 5} }},
            {ScoreBoard::ScoreType::FourDice, { {4, 5} }},
            {ScoreBoard::ScoreType::ChaseOff, { {} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(4), Dice(4), Dice(5), Dice(4), Dice(5)});
    EXPECT_EQ(10, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::FiveBeans));
    list = {
            {ScoreBoard::ScoreType::FourBeans, { {4, 3} }},
            {ScoreBoard::ScoreType::FiveBeans, { {5, 2} }},
            {ScoreBoard::ScoreType::FullHouse, { {5, 2}, {4, 3} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(1), Dice(2), Dice(4), Dice(5), Dice(6)});
    EXPECT_EQ(6, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::SixBeans));
    list = {
            {ScoreBoard::ScoreType::Aces, { {1, 1} }},
            {ScoreBoard::ScoreType::TwoBeans, { {2, 1} }},
            {ScoreBoard::ScoreType::FourBeans, { {4, 1} }},
            {ScoreBoard::ScoreType::FiveBeans, { {5, 1} }},
            {ScoreBoard::ScoreType::SixBeans, { {6, 1} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(1), Dice(1), Dice(2), Dice(2), Dice(2)});
    EXPECT_EQ(0, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::Choice));
    list = {
            {ScoreBoard::ScoreType::Aces, { {1, 2} }},
            {ScoreBoard::ScoreType::TwoBeans, { {2, 3} }},
            {ScoreBoard::ScoreType::FullHouse, { {1, 2}, {2, 3} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(2), Dice(3), Dice(1), Dice(1), Dice(1)});
    EXPECT_EQ(0, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::Choice));
    list = {
            {ScoreBoard::ScoreType::Aces, { {1, 3} }},
            {ScoreBoard::ScoreType::TwoBeans, { {2, 1} }},
            {ScoreBoard::ScoreType::ThreeBeans, { {3, 1} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(2), Dice(2), Dice(3), Dice(3), Dice(3)});
    EXPECT_EQ(13, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::FullHouse));
    list = {
            {ScoreBoard::ScoreType::TwoBeans, { {2, 2} }},
            {ScoreBoard::ScoreType::ThreeBeans, { {3, 3} }},
            {ScoreBoard::ScoreType::FullHouse, { {2, 2}, {3, 3} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(2), Dice(2), Dice(3), Dice(3), Dice(1)});
    EXPECT_EQ(0, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::FullHouse));
    list = {
            {ScoreBoard::ScoreType::Aces, { {1, 1} }},
            {ScoreBoard::ScoreType::TwoBeans, { {2, 2} }},
            {ScoreBoard::ScoreType::ThreeBeans, { {3, 2} }},
            {ScoreBoard::ScoreType::Choice, { {1, 1}, {2, 2}, {3, 2} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(3), Dice(3), Dice(3), Dice(3), Dice(3)});
    EXPECT_EQ(0, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::FullHouse));
    list = {
            {ScoreBoard::ScoreType::ThreeBeans, { {3, 5} }},
            {ScoreBoard::ScoreType::ChaseOff, { {} }},
            {ScoreBoard::ScoreType::FourDice, { {3, 5} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(5), Dice(5), Dice(5), Dice(5), Dice(4)});
    EXPECT_EQ(24, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::FourDice));
    list = {
            {ScoreBoard::ScoreType::FiveBeans, { {5, 4} }},
            {ScoreBoard::ScoreType::FourBeans, { {4, 1} }},
            {ScoreBoard::ScoreType::FourDice, { {{5, 4} , {4, 1}} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(5), Dice(5), Dice(5), Dice(5), Dice(5)});
    EXPECT_EQ(25, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::FourDice));
    list = {
            {ScoreBoard::ScoreType::FiveBeans, { {5, 5} }},
            {ScoreBoard::ScoreType::FourDice, { {5, 5} }},
            {ScoreBoard::ScoreType::ChaseOff, { {} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(2), Dice(3), Dice(4), Dice(5), Dice(6)});
    EXPECT_EQ(30, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::EvenStraight));
    list = {
            {ScoreBoard::ScoreType::FiveBeans, { {5, 1} }},
            {ScoreBoard::ScoreType::TwoBeans, { {2, 1} }},
            {ScoreBoard::ScoreType::ThreeBeans, { {3, 1} }},
            {ScoreBoard::ScoreType::FourBeans, { {4, 1} }},
            {ScoreBoard::ScoreType::SixBeans, { {6, 1} }},
            {ScoreBoard::ScoreType::EvenStraight, { {} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(1), Dice(2), Dice(3), Dice(4), Dice(5)});
    EXPECT_EQ(0, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::EvenStraight));
    list = {
            {ScoreBoard::ScoreType::FiveBeans, { {5, 1} }},
            {ScoreBoard::ScoreType::TwoBeans, { {2, 1} }},
            {ScoreBoard::ScoreType::ThreeBeans, { {3, 1} }},
            {ScoreBoard::ScoreType::FourBeans, { {4, 1} }},
            {ScoreBoard::ScoreType::Aces, { {1, 1} }},
            {ScoreBoard::ScoreType::Straight, { {} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(1), Dice(2), Dice(3), Dice(5), Dice(6)});
    EXPECT_EQ(0, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::EvenStraight));
    list = {
            {ScoreBoard::ScoreType::FiveBeans, { {5, 1} }},
            {ScoreBoard::ScoreType::TwoBeans, { {2, 1} }},
            {ScoreBoard::ScoreType::ThreeBeans, { {3, 1} }},
            {ScoreBoard::ScoreType::SixBeans, { {6, 1} }},
            {ScoreBoard::ScoreType::Aces, { {1, 1} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(1), Dice(2), Dice(3), Dice(4), Dice(5)});
    EXPECT_EQ(40, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::Straight));
    list = {
            {ScoreBoard::ScoreType::FiveBeans, { {5, 1} }},
            {ScoreBoard::ScoreType::TwoBeans, { {2, 1} }},
            {ScoreBoard::ScoreType::ThreeBeans, { {3, 1} }},
            {ScoreBoard::ScoreType::FourBeans, { {4, 1} }},
            {ScoreBoard::ScoreType::Aces, { {1, 1} }},
            {ScoreBoard::ScoreType::Straight, { {} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(2), Dice(3), Dice(4), Dice(5), Dice(6)});
    EXPECT_EQ(0, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::Straight));
    list = {
            {ScoreBoard::ScoreType::FiveBeans, { {5, 1} }},
            {ScoreBoard::ScoreType::TwoBeans, { {2, 1} }},
            {ScoreBoard::ScoreType::ThreeBeans, { {3, 1} }},
            {ScoreBoard::ScoreType::FourBeans, { {4, 1} }},
            {ScoreBoard::ScoreType::SixBeans, { {6, 1} }},
            {ScoreBoard::ScoreType::EvenStraight, { {} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(1), Dice(1), Dice(1), Dice(1), Dice(1)});
    EXPECT_EQ(50, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::ChaseOff));
    list = {
            {ScoreBoard::ScoreType::ChaseOff, { {} }},
            {ScoreBoard::ScoreType::Aces, { {1, 5} }},
            {ScoreBoard::ScoreType::FourDice, { {1, 5} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());

    game.setDice({Dice(6), Dice(6), Dice(6), Dice(6), Dice(6)});
    EXPECT_EQ(50, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::ChaseOff));
    list = {
            {ScoreBoard::ScoreType::ChaseOff, { {} }},
            {ScoreBoard::ScoreType::FourDice, { {6, 5} }},
            {ScoreBoard::ScoreType::SixBeans, { {6, 5} }},
    };
    EXPECT_EQ(list, game.getPosibleScores());
}

TEST(Chaser, outputUsedScore) {
    GameBoard game;
    game.makeDices();

    game.setDice({Dice(1), Dice(1), Dice(1), Dice(2), Dice(2)});
    ScoreBoard::ScoreList list = {
            {ScoreBoard::ScoreType::FullHouse, { {1, 3}, {2, 2} }},
    };
    game.choseScore(ScoreBoard::ScoreType::FullHouse);
    EXPECT_EQ(list, game.scoreBorad_.getUsedScore());

}
