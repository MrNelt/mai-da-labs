#include <cstddef>
#include <iostream>

#include <gtest/gtest.h>


#include <algorithm>

#include <chrono>
#include <random>
#include <string>


#include "avl.hpp"


std::mt19937 randomKey(std::chrono::steady_clock::now().time_since_epoch().count());


TEST(AvlTest, Benchmark) {
    const size_t countOfActions = 1000000;
    TAVlTree avl;
    std::map <std::string, unsigned long long> dict;
    std::vector <std::pair<std::string, unsigned long long>> dataInsert;
    std::vector <std::pair<std::string, unsigned long long>> dataErase;
    for (size_t i = 0; i < countOfActions; ++i) {
        std::string key = std::to_string(randomKey());
        unsigned long long value = randomKey();
        dataInsert.emplace_back(key, value);
        dataErase.emplace_back(key, value);
    }
    std::random_device randomDevice;
    std::mt19937 perm(randomDevice());
    std::shuffle(dataErase.begin(), dataErase.end(), perm);


    auto begin = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < countOfActions; ++i) {
        auto key = dataInsert[i].first;
        auto value = dataInsert[i].second;
        avl.Insert(key, value);
    }
    for (size_t i = 0; i < countOfActions; ++i) {
        auto key = dataInsert[i].first;
        avl.Erase(key);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto timeAVL = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();


    begin = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < countOfActions; ++i) {
        auto key = dataInsert[i].first;
        auto value = dataInsert[i].second;
        dict[key] = value;
    }
    for (size_t i = 0; i < countOfActions; ++i) {
        auto key = dataInsert[i].first;
        dict.erase(key);
    }
    end = std::chrono::high_resolution_clock::now();
    auto timeMAP = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();


    std::cout << "AVL time: " << timeAVL << " ms\n";
    std::cout << "std::map time: " << timeMAP << " ms\n";

}

