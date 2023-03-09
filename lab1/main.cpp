#include <iostream>

#include "radix_sort.h"


int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    std::vector <TNode> data;
    std::string first;
    std::string number;
    std::string second;
    std::string value;
    while (std::cin >> first >> number >> second >> value) {
        TNode elem;
        elem.value = new std::string;
        std::string key;
        key += first;
        key += " ";
        key += number;
        key += " ";
        key += second;
        elem.key = key;
        *elem.value = value;
        data.push_back(elem);
    }
    if (!data.empty()) {
        RadixSort(data, data.size());
    }
    for (const auto & elem : data) {
        std::cout << elem.key << "\t" << *elem.value << "\n";
        delete elem.value;
    }
}