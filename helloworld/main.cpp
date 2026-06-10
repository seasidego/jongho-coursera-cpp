#include <iostream>
#include <format> // C++20 표준 기능

int main() {
    // C++20 스타일의 문자열 포맷팅 테스트
    std::string message = std::format("Hello World! M1 Mac C++20 CMake Test Success!");
    std::cout << message << std::endl;
    return 0;
}
