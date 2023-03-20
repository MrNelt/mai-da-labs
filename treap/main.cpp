#include <iostream>
#include <string>

#include "treap.h"

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
        } else if (command == "exist") {
            int key;
            std::cin >> key;
            std::cout << treap.Exist(key) << '\n';
        } else if (command == "empty") {
            std::cout << treap.Empty() << "\n";
        } else if (command == "size") {
            std::cout << treap.Size() << "\n";
        } else if (command == "clear") {
            treap.Clear();
            std::cout << "Done!\n";
        } else if (command == "h") {
            std::cout << treap.Height() << "\n";
        } else {
            std::cout << "doesn't exist\n";
        }
    }
}