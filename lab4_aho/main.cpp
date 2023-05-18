#include <iostream>
#include <string>
#include <sstream>
#include "aho.hpp"


int main() {
    TAho aho;
    std::string line;
    std::getline(std::cin, line);
    int pid = 0;
    while (!line.empty()) {
        pid++;
        int num;
        auto stream = std::istringstream(line);
        std::vector<unsigned long long int> nums;
        while (stream >> num) {
            nums.push_back(num);
        }
        aho.AddVectorOfNums(nums, pid);
        std::getline(std::cin, line);
    }
    aho.Init();
    std::vector<std::pair<int, int>> info;
    std::vector<unsigned long long int> text;
    int page = 0;
    int num = 0;
    line = "";
    std::getline(std::cin, line);
    while (!line.empty()) {
        page++;
        auto stream = std::istringstream(line);
        num = 0;
        int elem;
        while (stream >> elem) {
            num++;
            text.push_back(elem);
            info.emplace_back(page, num);
        }
        std::getline(std::cin, line);
    }
    auto answers = aho.FindPosPatterns(text);;
    for (auto answer : answers) {
        std::cout << info[answer.first].first << ", " << info[answer.first].second << ", " << answer.second << "\n";
    }
}
