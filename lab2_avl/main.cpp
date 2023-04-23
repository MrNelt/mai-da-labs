#include <iostream>
#include <string>
#include <algorithm>

#include "avl.hpp"


int main() {
    TAVlTree avl;
    std::string command;
    while (std::cin >> command) {
        if (command == "+") {
            std::string key;
            unsigned long long value;
            std::cin >> key >> value;
            std::transform(key.begin(), key.end(), key.begin(),
                           [](unsigned char symb){ return std::tolower(symb); });
            if (avl.Exist(key).second) {
                std::cout << "Exist\n";
            } else {
                avl.Insert(key, value);
                std::cout << "OK\n";
            }
        }
        else if (command == "-") {
            std::string key;
            std::cin >> key;
            std::transform(key.begin(), key.end(), key.begin(),
                           [](unsigned char symb){ return std::tolower(symb); });
            if (!avl.Exist(key).second) {
                std::cout << "NoSuchWord\n";
            } else {
                avl.Erase(key);
                std::cout << "OK\n";
            }
        
        } else if (command == "!") {
            std::string action;
            std::cin >> action;
            std::string path;
            std::cin >> path;
            if (action == "Save") {   
                std::ofstream file(path, std::ios::binary | std::ios::trunc);
                auto size = avl.Size();
                file.write(reinterpret_cast<char*>(&size), sizeof(unsigned long long));
                if (size > 0) {
                    avl.SaveToFile(file);
                }
                std::cout << "OK\n";
                file.close();

            } else {
                std::ifstream file(path, std::ios::binary);
                avl.LoadFromFile(file);
                std::cout << "OK\n";
                file.close();
   
            }

        } else {
            std::transform(command.begin(), command.end(), command.begin(),
                           [](unsigned char symb){ return std::tolower(symb); });
            auto node = avl.Exist(command);
            if (node.second) {
                std::cout << "OK: " << node.first << "\n";
            } else {
                std::cout << "NoSuchWord\n";
            }
        }
    }
}