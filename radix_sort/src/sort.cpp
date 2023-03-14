#include "sort.h"
#include <cstddef>


void RadixSort(std::vector<int>& data) {
    const int sizeOfByte = 8;
    for (size_t i = 0; i < sizeof(int); ++i) {
        std::vector<int> count(1 << sizeOfByte);
        std::vector<int> res(data.size());
        for (int elem : data) {
            count[(elem >> (sizeOfByte * i)) & ((1 << sizeOfByte) - 1)]++;
        }
        for (size_t j = 1; j < count.size(); ++j) {
            count[j] += count[j - 1];
        }
        for (size_t j = data.size(); j > 0; j--) {
            int elem = data[j - 1];
            int index = count[(elem >> (sizeOfByte * i)) & ((1 << sizeOfByte) - 1)];
            res[index - 1] = elem;
            count[(elem >> (sizeOfByte * i)) & ((1 << sizeOfByte) - 1)]--;
        }
        data = res;
    }
}