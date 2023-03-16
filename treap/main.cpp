#include <iostream>
#include <string>

#include "treap.hpp"

int main() {
    TTreap treap;
    std::string command;
    while (std::cin >> command) {
        if (command == "+") {
            int key;
            std::cin >> key;
            treap.Insert(key);
        } else if (command == "-") {
            int key;
            std::cin >> key;
            treap.Erase(key);
        } else if (command == "print") {
            treap.Print();
        } else if (command == "exist"){
            int key;
            std::cin >> key;
            std::cout << treap.Exist(key) << '\n';
        } else {
            std::cout << "command doesn't exist\n";
        }
    }
}