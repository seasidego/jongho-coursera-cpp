#include <iostream>
#include <format>
#include <vector>

class BinaryTree {
public :
    class Node {
    public :

        Node* left_ = nullptr;
        Node* right_ = nullptr;
        int value_ = 0;

        Node(int value) {
            value_ = value;
        }
    };

    Node* head_ = nullptr;

    BinaryTree(int head) {
        Node* n = new Node(head);
        head_ = n;
    }
    
    Node* find(int value, Node* current) const {
        if (current->value_ == value) {
            return current;
        } else if (current->value_ < value) {
            if (current->right_ == nullptr) {
                return nullptr;
            }
            return find(value, current->right_);
        } else {
            if (current->left_ == nullptr) {
                return nullptr;
            }
            return find(value, current->left_);
        }
    }

    void add(int value, Node* current) const {
        if (current->value_ < value) {
            if (current->right_ == nullptr) {
                current->right_ = new Node(value);
                return ;
            }
            add(value, current->right_);
        } else {
            if (current->left_ == nullptr) {
                current->left_ = new Node(value);
                return ;
            }
            add(value, current->left_);
        }
    }

    void print(Node* current, int deep, bool isRight) const {
        if (isRight) {
            std::cout << "right ";
        } else {
            std::cout << "left  ";
        }
        std::cout << deep << ": " <<  current->value_ << std::endl;

        if (current->right_ != nullptr) {
            print(current->right_, deep + 1, true);
        }
        if (current->left_ != nullptr) {
            print(current->left_, deep + 1, false);
        }
    }

    void addValue(int value) {
        add(value, head_);
    }

    void clear(Node* current) {
        if (current->right_ != nullptr) {
            clear(current->right_);
        }
        if (current->left_ != nullptr) {
            clear(current->left_);
        }
        std::cout << "delete: " << current->value_ << std::endl;    
        delete current;
    }

    void findAndPrint(int value) {
        Node* found = find(value, head_);
        if (found == nullptr) {
            std::cout << "no_value" << std::endl;    
            return ;
        }
        std::cout << found->value_ << std::endl;    
        return ;
    }

    void printAll() {
        print(head_, 0, false);
    }

    ~BinaryTree() {
        clear(head_);
    }
};

int main() {
    BinaryTree b = BinaryTree(10);
    b.addValue(15);
    b.addValue(8);
    b.addValue(32);
    b.addValue(1);
    b.addValue(2);

    b.printAll();

    b.findAndPrint(100);
}