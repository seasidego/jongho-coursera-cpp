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

    game.setDice({Dice(2), Dice(2), Dice(6), Dice(2), Dice(1)});
    EXPECT_EQ(6, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::TwoBeans));

    game.setDice({Dice(2), Dice(2), Dice(6), Dice(2), Dice(3)});
    EXPECT_EQ(3, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::ThreeBeans));

    game.setDice({Dice(4), Dice(4), Dice(4), Dice(4), Dice(4)});
    EXPECT_EQ(20, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::FourBeans));

    game.setDice({Dice(4), Dice(4), Dice(5), Dice(4), Dice(5)});
    EXPECT_EQ(10, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::FiveBeans));

    game.setDice({Dice(1), Dice(2), Dice(4), Dice(5), Dice(6)});
    EXPECT_EQ(6, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::SixBeans));

    game.setDice({Dice(1), Dice(1), Dice(2), Dice(2), Dice(2)});
    EXPECT_EQ(0, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::Choice));

    game.setDice({Dice(2), Dice(3), Dice(1), Dice(1), Dice(1)});
    EXPECT_EQ(0, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::Choice));

    game.setDice({Dice(2), Dice(2), Dice(3), Dice(3), Dice(3)});
    EXPECT_EQ(13, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::FullHouse));

    game.setDice({Dice(2), Dice(2), Dice(3), Dice(3), Dice(1)});
    EXPECT_EQ(0, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::FullHouse));

    game.setDice({Dice(3), Dice(3), Dice(3), Dice(3), Dice(3)});
    EXPECT_EQ(0, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::FullHouse));

    game.setDice({Dice(5), Dice(5), Dice(5), Dice(5), Dice(4)});
    EXPECT_EQ(24, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::FourDice));

    game.setDice({Dice(5), Dice(5), Dice(5), Dice(5), Dice(5)});
    EXPECT_EQ(25, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::FourDice));

    game.setDice({Dice(2), Dice(3), Dice(4), Dice(5), Dice(6)});
    EXPECT_EQ(30, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::EvenStraight));

    game.setDice({Dice(1), Dice(2), Dice(3), Dice(4), Dice(5)});
    EXPECT_EQ(0, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::EvenStraight));

    game.setDice({Dice(1), Dice(2), Dice(3), Dice(5), Dice(6)});
    EXPECT_EQ(0, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::EvenStraight));

    game.setDice({Dice(1), Dice(2), Dice(3), Dice(4), Dice(5)});
    EXPECT_EQ(40, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::Straight));

    game.setDice({Dice(2), Dice(3), Dice(4), Dice(5), Dice(6)});
    EXPECT_EQ(0, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::Straight));

    game.setDice({Dice(1), Dice(1), Dice(1), Dice(1), Dice(1)});
    EXPECT_EQ(50, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::ChaseOff));

    game.setDice({Dice(6), Dice(6), Dice(6), Dice(6), Dice(6)});
    EXPECT_EQ(50, game.scoreBorad_.calculateScore(game.dices_, ScoreBoard::ScoreType::ChaseOff));
}
