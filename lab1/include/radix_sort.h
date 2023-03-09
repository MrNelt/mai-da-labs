#ifndef RADIX_SORT_H
#define RADIX_SORT_H

#include <iostream>
#include <string>
#include <vector>

struct TNode {
    static const size_t KEY_SIZE = 8;
    static const size_t DIGIT_SIZE = 128;
    std::string key;
    std::string *value;
    int GetValue(size_t n) {
        return static_cast<int>(key[n]);
    };
};


void RadixSort(std::vector <TNode>& data, size_t n);

#endif