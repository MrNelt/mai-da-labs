#include <iostream>

#include <gtest/gtest.h>


#include <algorithm>

#include <chrono>
#include <random>


#include "avl.hpp"


std::mt19937 randomKey(std::chrono::steady_clock::now().time_since_epoch().count());


TEST(AvlTest, MyTest) {
    TAVlTree avl;
    avl.Insert(1);
    avl.Insert(2);
    EXPECT_EQ(2, avl.Size());
    avl.Clear();
    EXPECT_EQ(0, avl.Size());
}

TEST(AvlTest, CommonTest) {
    size_t const countActions = 5000;
    TAVlTree avl;
    std::vector <int> keys;
    for (size_t i = 0; i < countActions; ++i) {
        int key = static_cast<int>(randomKey());
        avl.Insert(key);
        keys.push_back(key);
        EXPECT_EQ(i + 1, avl.Size());
    }
    std::random_device randomDevice;
    std::mt19937 perm(randomDevice());
    std::shuffle(keys.begin(), keys.end(), perm);
    for (size_t i = 0; i < countActions; ++i) {
        int key = keys[i];
        EXPECT_EQ(avl.Exist(key), true);
        avl.Erase(key);
        EXPECT_EQ(countActions - i - 1, avl.Size());
    }
    EXPECT_EQ(avl.Empty(), true);
}

TEST(AvlTest, HeightTest) {
    size_t const countNodes = 1000000;
    TAVlTree avl;
    for (size_t i = 0; i < countNodes; ++i) {
        int key = static_cast<int>(randomKey());
        avl.Insert(key);
    }
    std::cout << "Height: " << avl.HeightTree() << std::endl;
}
