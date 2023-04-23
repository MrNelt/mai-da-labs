#include <iostream>
#include <string>

#include "avl.hpp"

int main() {
    TAVlTree avl;
    std::string command;
    while (std::cin >> command) {
        if (command == "+") {
            int key;
            std::cin >> key;
            avl.Insert(key);
        } else if (command == "-") {
            int key;
            std::cin >> key;
            avl.Erase(key);
        } else if (command == "exist") {
            int key;
            std::cin >> key;
            std::cout << avl.Exist(key) << '\n';
        } else if (command == "empty") {
            std::cout << avl.Empty() << "\n";
        } else if (command == "size") {
            std::cout << avl.Size() << "\n";
        } else if (command == "clear") {
            avl.Clear();
            std::cout << "Done!\n";
        } else if (command == "save") {
            std::string path;
            std::cin >> path;
            std::ofstream file(path, std::ios::binary | std::ios::app);
            avl.SaveToFile(file);
        } else if (command == "load") {
            std::string path;
            std::cin >> path;
            std::ifstream file(path, std::ios::binary | std::ios::app);
            avl.LoadFromFile(file);
        } else {
            std::cout << "doesn't exist\n";
        }
    }
}