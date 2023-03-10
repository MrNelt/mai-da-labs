#include <algorithm>
#include <cstddef>
#include <gtest/gtest.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "radix_sort.h"

bool CompTNode(const TNode& lhs, const TNode& rhs) {
    return lhs.key < rhs.key;
}

namespace NDatagen {
    const size_t ALPHA_SIZE = 26;
    const size_t NUM_SIZE = 10;

    std::string GenerateValue(size_t n) {
        std::string str;
        for (size_t i = 0; i < n; ++i) {
            str += static_cast<char>(static_cast<int>('A') + rand() % ALPHA_SIZE);
        }
        return str;
    }

    std::string GenerateKey() {
        std::string key;
        std::string first;
        std::string num;
        std::string second;
        first += static_cast<char>(static_cast<int>('A') + rand() % ALPHA_SIZE);
        num += static_cast<char>(static_cast<int>('0') + rand() % NUM_SIZE);
        num += static_cast<char>(static_cast<int>('0') + rand() % NUM_SIZE);
        num += static_cast<char>(static_cast<int>('0') + rand() % NUM_SIZE);
        second += static_cast<char>(static_cast<int>('A') + rand() % ALPHA_SIZE);
        second += static_cast<char>(static_cast<int>('A') + rand() % ALPHA_SIZE);
        key += first;
        key += ' ';
        key += num;
        key += ' ';
        key += second;
        return key;
    }

    std::vector <TNode> GenerateNode(size_t n) {
        const size_t valueSize = 64;
        srand(time(nullptr));
        std::vector <TNode> data;
        for (size_t i = 0; i < n; ++i) {
            TNode elem;
            elem.value = new std::string;
            *elem.value = GenerateValue(valueSize);
            elem.key = GenerateKey();
            data.push_back(elem);
        }
        return data;
    }
}

TEST(Lab1Test, StableTest) {
    const size_t size = 5;
    std::vector <std::pair<std::string, std::string>> data {
        {"A 000 AA", "AAA1"},
        {"A 000 AA", "AAA2"},
        {"A 000 AA", "AAA3"},
        {"A 000 AA", "AAA4"},
        {"A 000 AA", "AAA5"}
    };
    std::vector <TNode> input(size);
    std::vector <TNode> output(size);
    for (size_t i = 0; i < size; ++i) {
        input[i].value = new std::string;
        *input[i].value = data[i].second;
        input[i].key = data[i].first;

        output[i].value = new std::string;
        *output[i].value = data[i].second;
        output[i].key = data[i].first;
    }
    RadixSort(input, size);
    ASSERT_EQ(input.size(), output.size());
    for (size_t i = 0; i < size; ++i) {
        EXPECT_EQ(input[i].key, output[i].key);
        EXPECT_EQ(*input[i].value, *output[i].value);
    }
}

TEST(Lab1Test, CommonTest) {
    const size_t size = 50000;
    auto input = NDatagen::GenerateNode(size);
    auto output = input;
    std::stable_sort(output.begin(), output.end(), CompTNode);

    RadixSort(input, size);
    ASSERT_EQ(input.size(), output.size());

    for (size_t i = 0; i < size; ++i) {
        EXPECT_EQ(input[i].key, output[i].key);
        EXPECT_EQ(*input[i].value, *output[i].value);
    }

}

TEST(Lab1Test, Benchmark) {
    const size_t size = 1000000;
    auto input1 = NDatagen::GenerateNode(size);
    auto input2 = input1;

    auto begin1 = std::chrono::high_resolution_clock::now();
    RadixSort(input1, size);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin1).count();


    auto begin2 = std::chrono::high_resolution_clock::now();
    std::stable_sort(input2.begin(), input2.end(), CompTNode);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto time2= std::chrono::duration_cast<std::chrono::milliseconds>(end2 - begin2).count();
    std::cout << "RadixSort milli: " << time1 << "\n";
    std::cout << "std::stable_sort milli: " << time2 << "\n";

    EXPECT_GE(time2, time1);

}