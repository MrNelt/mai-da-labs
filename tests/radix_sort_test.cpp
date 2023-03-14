#include <algorithm>
#include <cstddef>
#include <gtest/gtest.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "sort.h"

namespace NDatagen {
    std::vector<int> GenerateVector(size_t size) {
        srand(time(nullptr));
        std::vector<int> data(size);
        for (size_t i = 0; i < size; ++i) {
            data[i] = rand();
        }
        return data;
    }
}

TEST(RadixSortTest, CommonTest) {
    const size_t size = 50000;
    auto input = NDatagen::GenerateVector(size);
    auto output = input;
    std::sort(output.begin(), output.end());
    RadixSort(input);
    ASSERT_EQ(output.size(), input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        EXPECT_EQ(input[i], output[i]);
    }
}


TEST(RadixSortTest, Banchmark) {
    const size_t size = 5000000;
    auto input1 = NDatagen::GenerateVector(size);
    auto input2 = input1;

    auto begin1 = std::chrono::high_resolution_clock::now();
    RadixSort(input1);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin1).count();


    auto begin2 = std::chrono::high_resolution_clock::now();
    std::sort(input2.begin(), input2.end());
    auto end2 = std::chrono::high_resolution_clock::now();
    auto time2= std::chrono::duration_cast<std::chrono::milliseconds>(end2 - begin2).count();
    std::cout << "RadixSort time: " << time1 << " ms\n";
    std::cout << "std::sort time: " << time2 << " ms\n";

    EXPECT_GE(time2, time1);

}


