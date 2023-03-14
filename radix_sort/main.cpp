#include <cstddef>
#include <iostream>

#include "sort.h"

int main() {
    size_t size;
    std::cin >> size;
    std::vector<int> data(size);
    std::cout << sizeof(int) << "\n";
    for (int & elem : data) {
        std::cin >> elem;
        // std::cout << (elem & ((255))) << " ";
    }
    // std::cout << "\n";
    RadixSort(data);
    for (int & elem : data) {
        std::cout << elem << " ";

    }
    std::cout << "\n";
}