#include <iostream>
#include <string>
#include <algorithm>

#include "treap.h"



int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    TTreap treap;
    std::string command;
    while (std::cin >> command) {
        if (command == "+") {
            std::string key;
            unsigned long long value;
            std::cin >> key >> value;
            std::transform(key.begin(), key.end(), key.begin(),
                           [](unsigned char symb){ return std::tolower(symb); });
            if (treap.Exist(key).second) {
                std::cout << "Exist\n";
            } else {
                treap.Insert(key, value);
                std::cout << "OK\n";
            }
        }
        else if (command == "-") {
            std::string key;
            std::cin >> key;
            std::transform(key.begin(), key.end(), key.begin(),
                           [](unsigned char symb){ return std::tolower(symb); });
            if (!treap.Exist(key).second) {
                std::cout << "NoSuchWord\n";
            } else {
                treap.Erase(key);
                std::cout << "OK\n";
            }
        } else {
            std::transform(command.begin(), command.end(), command.begin(),
                           [](unsigned char symb){ return std::tolower(symb); });
            auto node = treap.Exist(command);
            if (node.second) {
                std::cout << "OK: " << node.first << "\n";
            } else {
                std::cout << "NoSuchWord\n";
            }
        }
    }
}