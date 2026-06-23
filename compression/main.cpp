#include <iostream>
#include <format>
#include <map>
#include <ranges>
#include <string>
#include <vector>
#include <memory>
#include <set>
#include <utility>
#include <algorithm>
#include <sstream>

class Line {
public:

    std::string line_ = "";

    void write(std::string line) {
        line_ = line;
    }

    // There are no spaces between words.
    // std::vector<bool> compression() {
    //     std::vector<char> chars(line_.begin(), line_.end());
    //     std::map<char, int> frequency;
    //     for (const auto& c : chars) {
    //         frequency[c]++;
    //     }

    //     std::vector<std::pair<char, int>> vecFrequency(frequency.begin(), frequency.end());

    //     std::sort(vecFrequency.begin(), vecFrequency.end(), [](const auto& a, const auto& b) {
    //         return a.second > b.second;
    //     });

    //     std::map<char, std::vector<bool>> code;

    //     int index = 0;
    //     std::vector<bool> boolStacked;
    //     for (const auto& v : vecFrequency) {
    //         std::vector<bool> boolLine(boolStacked);

    //         if (index + 1 == vecFrequency.size()) {
    //             code[v.first] = boolLine;

    //             break;
    //         }

    //         if (vecFrequency[index].second >= getSum(vecFrequency, index + 1)) {
    //             boolLine.emplace_back(true);
    //             boolStacked.emplace_back(false);
    //         } else {
    //             boolLine.emplace_back(false);
    //             boolStacked.emplace_back(true);
    //         }
    //         code[v.first] = boolLine;
    //         index++;
    //     }

    //     std::vector<bool> codedLine;
    //     for (const auto& c : chars) {
    //         const auto it = code.find(c);
    //         if (it != code.end()) {
    //             codedLine.insert(codedLine.end(), it->second.begin(), it->second.end());
    //         }
    //     }

    //     return codedLine;
    // }

    std::vector<std::vector<bool>> compressionForPrint() {
        std::vector<char> chars(line_.begin(), line_.end());
        std::map<char, int> frequency;
        for (const auto& c : chars) {
            frequency[c]++;
        }

        std::vector<std::pair<char, int>> vecFrequency(frequency.begin(), frequency.end());

        std::sort(vecFrequency.begin(), vecFrequency.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        std::map<char, std::vector<bool>> code;

        int index = 0;
        std::vector<bool> boolStacked;
        for (const auto& v : vecFrequency) {
            std::vector<bool> boolLine(boolStacked);

            if (index + 1 == vecFrequency.size()) {
                code[v.first] = boolLine;

                break;
            }

            if (vecFrequency[index].second >= getSum(vecFrequency, index + 1)) {
                boolLine.emplace_back(true);
                boolStacked.emplace_back(false);
            } else {
                boolLine.emplace_back(false);
                boolStacked.emplace_back(true);
            }
            code[v.first] = boolLine;
            index++;
        }

        std::vector<std::vector<bool>> codedLine;
        for (const auto& c : chars) {
            const auto it = code.find(c);
            if (it != code.end()) {
                codedLine.emplace_back(it->second);
            }
        }

        return codedLine;
    }

    int getSum(std::vector<std::pair<char, int>> vecFrequency, int start) {
        int index = 0;
        int result = 0;
        for (const auto& n : vecFrequency) {
            if (index >= start) {
                result += n.second;
            }
            index++;
        }
        return result;
    }

};


int main() {

    Line line;
    line.write("abbcccddddeeeee");
    // for (const auto& code : line.compression())  {
    //     if (code) {
    //         std::cout << "1";
    //     } else {
    //         std::cout << "0";
    //     }
    // }
    // std::cout << std::endl;
    std::cout << "input :" << std::endl;
    std::cout << line.line_ << std::endl;

    std::cout << "output :" << std::endl;
    for (const auto& vec : line.compressionForPrint())  {
        for (const auto& code : vec) {
            if (code) {
                std::cout << "1";
            } else {
                std::cout << "0";
            }
        }
        std::cout << " ";
    }
    std::cout << std::endl;

    // expected output
    // input :
    // abbcccddddeeeee
    // output :
    // 1100 1101 1101 111 111 111 10 10 10 10 0 0 0 0 0

    return 0;
}
