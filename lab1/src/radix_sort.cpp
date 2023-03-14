#include "radix_sort.h"


void RadixSort(std::vector<TNode> &data, size_t n) {
    for (size_t i = TNode::KEY_SIZE; i > 0; --i) {
        std::vector <TNode> result(n);
        std::vector <int> count(TNode::DIGIT_SIZE);
        for (size_t j = 0; j < n; ++j) {
            count[data[j].GetValue(i - 1)]++;
        }
        for (size_t j = 1; j < TNode::DIGIT_SIZE; ++j) {
            count[j] += count[j - 1];
        }
        for (size_t j = n; j > 0; j--) {
            int index = count[data[j - 1].GetValue(i - 1)];
            result[index - 1] = data[j - 1];
            count[data[j - 1].GetValue(i - 1)]--;
        }
        data = std::move(result);
    }
}