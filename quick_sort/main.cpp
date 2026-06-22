#include <iostream>
#include <format>
#include <vector>

std::vector<int> quickSort(std::vector<int> list) {
    if (list.size() <= 0) {
        return {};
    }
    if (list.size() == 1) {
        return list;
    }

    std::vector<int> left = {};
    std::vector<int> right = {};
    std::vector<int> combined = {};
    std::vector<int> temp_combined = {};
    int p  = list[0];
    for (int i = 1; i < list.size(); i++) {
        if (list[i] < p) {
            left.emplace_back(list[i]);
        } else {
            right.emplace_back(list[i]);
        }
    }

    // std::cout << "___________________left" << std::endl;
    // for (const auto& i : left) {
    //     std::cout << i << std::endl;
    // }
    // std::cout << "___________________right" << std::endl;
    // for (const auto& i : right) {
    //     std::cout << i << std::endl;
    // }

    // temp_combined = left;
    // temp_combined.emplace_back(p);
    // temp_combined.insert(temp_combined.end(), right.begin(), right.end());

    // std::cout << "_______________________temp_combined" << std::endl;
    // for (const auto& i : temp_combined) {
    //     std::cout << i << std::endl;
    // }

    // on the second thought, i dont have to do this
    // if (right.size() == list.size() && left.size() == 0) { // situation that just have right with two value -> it keeps repeat so it stopts it
    //     return right;
    // }

    left = quickSort(left);
    right = quickSort(right);

    combined = left;
    combined.emplace_back(p);
    combined.insert(combined.end(), right.begin(), right.end());

    // std::cout << "_______________________combined" << std::endl;
    // for (const auto& i : combined) {
    //     std::cout << i << std::endl;
    // }

    return combined;
}

int main() {
    std::vector<int> list = {10, 12, 55, 4, 78, 16, 95, 47, 98, 1, 6, 14, 22, 10, 55, 95};
    // std::vector<int> list = {10, 10, 13, 9, 9, 13, 13, 13, 13, 10, 9, 10, 9, 10};
    // std::vector<int> list = {1, 2, 3, 9, 1, 2, 3, 9, 1, 2, 3, 9};

    std::vector<int> sortedList = quickSort(list);
    // std::cout << "___________________" << std::endl;
    for (const auto& i : sortedList) {
        std::cout << i << std::endl;
    }
}
