#include <iostream>
#include <format>
#include <map>
#include <vector>
#include <memory>
#include <set>
#include <utility>
#include <algorithm>

class Graph {
public:
    using Key = int;
    using Neighbors = std::set<Key>;
    using Nodes = std::map<Key, Neighbors>;

    Nodes nodes_ = {};

    void addNode(const Key& value) {
        nodes_.emplace(value, Neighbors{});
    }

    void addNeighbors(const Key& k, const Neighbors& ns) {
        auto node = nodes_.find(k);
        if (node == nodes_.end()) {
            return;
        }

        // if any neighbor is not in the graph, then stop.
        for (const auto& n : ns) {
            auto neighbor = nodes_.find(n);
            if (neighbor == nodes_.end() || neighbor->first == node->first) {
                continue;
            }
            node->second.insert(n);
            neighbor->second.insert(k);
        }
    }

    void print() const {
        for (const auto& n : nodes_) {
            std::cout << n.first << " : ";
            for (const auto& ne : n.second) {
                std::cout << ne << ", ";
            }
            std::cout << std::endl;
        }
    }

    int findPath(const Key& start, const Key& current, std::set<Key> passed, const Key& end, int deep) const {
        auto curNode = nodes_.find(current);
        if (curNode == nodes_.end()) {
            return -1;
        }
        auto endNode = nodes_.find(end);
        if (endNode == nodes_.end()) {
            return -1;
        }


        std::vector<int> results = {};
        deep += 1;
        passed.insert(current);

        for (const auto& ne : curNode->second) {
            bool isPassed = false;
            if (ne == end) {
                std::cout << "passed: ";
                for (const auto& p : passed) {
                    std::cout << p << " ";
                }
                std::cout << std::endl;

                return deep;
            }

            for (const auto& p : passed) {
                if (ne == p) {
                    isPassed = true;
                    break;
                }
            }
            // if this add -1, in min finder, in causes bug.
            if (!isPassed) {
                int result = findPath(start, ne, passed, end, deep);
                if (result > 0) {
                    results.emplace_back(result);
                }
            }
        }

        // Can get iterater's true value.
        if (results.size() > 0) {
            return *std::min_element(results.begin(), results.end());
        }

        return -1;
    }
};


int main() {
    Graph g = Graph();
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);
    g.addNode(4);
    g.addNode(5);
    g.addNode(6);
    g.addNode(7);
    g.addNode(8);
    g.addNode(9);

    g.addNeighbors(1, {5, 2, 3, 4, 7});
    g.addNeighbors(2, {6});
    g.addNeighbors(3, {5});
    g.addNeighbors(4, {7, 8});
    g.addNeighbors(5, {6, 7});
    g.addNeighbors(7, {9});
    g.addNeighbors(8, {9});
    g.print();
    int minPass = g.findPath(1, 1, {}, 9, 0);
    std::cout << "min find path: " << minPass << std::endl;

    // expected output
    // 1 : 2, 3, 4, 5, 7,
    // 2 : 1, 6,
    // 3 : 1, 5,
    // 4 : 1, 7, 8,
    // 5 : 1, 3, 6, 7,
    // 6 : 2, 5,
    // 7 : 1, 4, 5, 9,
    // 8 : 4, 9,
    // 9 : 7, 8,
    // passed: 1 2 4 5 6 7 8
    // passed: 1 2 5 6 7
    // passed: 1 3 4 5 7 8
    // passed: 1 3 5 7
    // passed: 1 4 7
    // passed: 1 4 8
    // passed: 1 4 5 7 8
    // passed: 1 5 7
    // passed: 1 4 7 8
    // passed: 1 7
    // min find pass: 2
}
