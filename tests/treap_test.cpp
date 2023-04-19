#include <algorithm>
#include <gtest/gtest.h>
#include <chrono>


#include "treap.h"


std::mt19937 randomKey(std::chrono::steady_clock::now().time_since_epoch().count());


TEST(TreapTest, MyTest) {
    TTreap treap;
    treap.Insert(1);
    treap.Insert(2);
    EXPECT_EQ(2, treap.Size());
    treap.Clear();
    EXPECT_EQ(0, treap.Size());
}

TEST(TreapTest, CommonTest) {
    size_t const countActions = 5000;
    TTreap treap;
    std::vector <int> keys;
    for (size_t i = 0; i < countActions; ++i) {
        int key = static_cast<int>(randomKey());
        treap.Insert(key);
        keys.push_back(key);
        EXPECT_EQ(i + 1, treap.Size());
    }
    std::random_device randomDevice;
    std::mt19937 perm(randomDevice());
    std::shuffle(keys.begin(), keys.end(), perm);
    for (size_t i = 0; i < countActions; ++i) {
        int key = keys[i];
        EXPECT_EQ(treap.Exist(key), true);
        treap.Erase(key);
        EXPECT_EQ(countActions - i - 1, treap.Size());
    }
    EXPECT_EQ(treap.Empty(), true);
}

TEST(TreapTest, HeightTest) {
    size_t const countNodes = 1000000;
    TTreap treap;
    for (size_t i = 0; i < countNodes; ++i) {
        int key = static_cast<int>(randomKey());
        treap.Insert(key);
    }
    std::cout << "Height: " << treap.Height() << std::endl;
}
