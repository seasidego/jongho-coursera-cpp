#include <iostream>
#include <format>
#include <map>
#include <ranges>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <set>
#include <utility>
#include <algorithm>
#include <sstream>

class HuffmanCode {
public:
    using DataType = char;
    using Data = std::vector<DataType>;
    using Compressed = std::vector<bool>;
    using CompressionCode = std::map<DataType, Compressed>;
    using Frequency = std::map<DataType, int>;  // <DataType, count>
    using UncompressionCode = std::map<Compressed, DataType>;

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

    std::pair<UncompressionCode, std::vector<Compressed>> compressionForPrint(const std::string& line) const {
        Data chars(line.begin(), line.end());
        Frequency frequency;
        for (const auto& c : chars) {
            frequency[c]++;
        }

        // to sort frequency, used vector to contain char and int.
        std::vector<std::pair<char, int>> vecFrequency(frequency.begin(), frequency.end());

        std::sort(vecFrequency.begin(), vecFrequency.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        CompressionCode code;

        int index = 0;
        Compressed boolStacked;
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

        std::vector<Compressed> compressedLine;
        for (const auto& c : chars) {
            const auto it = code.find(c);
            if (it != code.end()) {
                compressedLine.emplace_back(it->second);
            }
        }

        UncompressionCode codeForUncompression;
        for (const auto& c : code) {
            codeForUncompression.emplace(c.second, c.first);
        }

        return std::make_pair(codeForUncompression, compressedLine);
    }

    int getSum(const std::vector<std::pair<char, int>>& vecFrequency, int start) const {
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

    std::string uncompression(std::pair<UncompressionCode, std::vector<Compressed>> codeAndCompressedData) const{
        const auto& code = codeAndCompressedData.first;
        const auto& compressedData = codeAndCompressedData.second;
        Data data;
        for (const auto& v : compressedData) {
            auto it = code.find(v);
            if (it != code.end()) {
                data.emplace_back(it->second);
            } else {
                // if compressed data can not be found in the code, it will be replaced with '!'".
                data.emplace_back('!');
            }
        }

        std::string stringData(data.begin(), data.end());
        return stringData;
    }
};

int main() {

    HuffmanCode huffmanCode;

    // for (const auto& code : line.compression())  {
    //     if (code) {
    //         std::cout << "1";
    //     } else {
    //         std::cout << "0";
    //     }
    // }
    // std::cout << std::endl;
    std::string inputLine = "abbcccddddeeeee";
    std::cout << "input :" << std::endl;
    std::cout << inputLine << std::endl << std::endl;

    std::cout << "output:" << std::endl;
    std::cout << "code: ";
    const auto& codeAndCompressedData = huffmanCode.compressionForPrint(inputLine);

    for (const auto& vec : codeAndCompressedData.first)  {
        std::cout << vec.second << ": ";
        for (const auto& code : vec.first) {
            if (code) {
                std::cout << "1";
            } else {
                std::cout << "0";
            }
        }
        std::cout << "  ";
    }
    std::cout << std::endl;

    std::cout << "compressed line: ";

    for (const auto& compressed : codeAndCompressedData.second)  {
        for (const auto& code : compressed) {
            if (code) {
                std::cout << "1";
            } else {
                std::cout << "0";
            }
        }
        std::cout << " ";
    }
    std::cout << std::endl;

    std::cout << "uncompressed line: ";
    std::cout << huffmanCode.uncompression(codeAndCompressedData)<< std::endl;


    // expected output
    // input :
    // abbcccddddeeeee

    // output:
    // code: e: 0  d: 10  a: 1100  b: 1101  c: 111
    // compressed line: 1100 1101 1101 111 111 111 10 10 10 10 0 0 0 0 0
    // uncompressed line: abbcccddddeeeee

    return 0;
}
