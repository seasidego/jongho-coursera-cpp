#include <iostream>
#include <format>
#include <vector>
#include "chaser.h"
#include <gtest/gtest.h>

//int main() {
// -> 아래와 같이 argc, argv 받을 수 있도록 변경
int main(int argc, char **argv) {

    for (int i = 0; i < argc ; i++) {
        // 실행할 때 arg에 gtest가 있으면
        if (std::strcmp(argv[i], "gtest") == 0) {
            // google test에 argc, arg 전달
            ::testing::InitGoogleTest(&argc, argv);

            // 여기서 모든 테스트 실행
            return RUN_ALL_TESTS();
        }
    }

    // 총점 출력, 기록판 출력, 이미 했던 점수 제외, 기록시 숫자로 입력가능하게
    GameBoard game;
    game.turnAutoSort();
    game.makeDices();

    while (true) {

        game.rollDices();
        // game.setDice({Dice(3), Dice(3), Dice(6), Dice(6), Dice(5)});

        game.printDices();
        game.sortPrintDices();

        for (int i = 0; i < 2; i++) {
            game.rollSelectedDices();
            game.printDices();
            game.sortPrintDices();
        }

        game.printPosibleScores();
        game.choseScore();
    }
}
