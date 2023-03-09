#include <iostream>
#include <string>
#include <vector>

struct TNode {
    static const size_t KEY_SIZE = 8;
    static const size_t DIGIT_SIZE = 128;
    std::string key;
    std::string* value;
    int GetValue(size_t n) {
        return static_cast<int>(key[n]);
    };
};

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
        for (size_t j = 0; j < n; ++j) {
            data[j] = result[j];
        }
    }
}

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