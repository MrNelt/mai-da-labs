#include <iostream>
#include <gtest/gtest.h>
#include <random>
#include <chrono>

#include "aho.hpp"

std::mt19937 randomKey(std::chrono::steady_clock::now().time_since_epoch().count());

std::vector<std::pair<unsigned long long, unsigned long long >> WeakAlgo(std::vector<std::vector<unsigned long long>>& patterns, std::vector<unsigned long long>& text) {
    std::vector<std::pair<unsigned long long, unsigned long long>> answer;
    for (size_t i = 0; i < text.size(); ++i) {
        for (size_t j = 0; j < patterns.size(); ++j) {
            auto count = patterns[j].size();
            if (i + count > text.size()) {
                continue;
            }
            int flag = 0;
            for (size_t k = i, m = 0; m < count; k++, m++) {
                if (text[k] != patterns[j][m]) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                answer.emplace_back(i, j + 1);
            }
        }
    }
    return answer;
}


TEST(Lab4Test, CommonTest) {
    std::vector <unsigned long long> text;
    const int countWords = 1000;
    const int countPatterns = 1000;
    std::vector <std::vector<unsigned long long >> patterns(countPatterns);
    for (size_t i = 0; i < countWords; ++i) {
        text.push_back(randomKey() % 2 + 1);
    }
    for (size_t i = 0; i < countPatterns; ++i) {
        auto sizePattern = randomKey() % 100 + 1;
        std::vector <unsigned long long> pattern;
        for (size_t j = 0; j < sizePattern; ++j) {
            pattern.push_back(randomKey() % 2 + 1);
        }
        patterns[i] = pattern;
    }
    TAho aho;
    for (size_t i = 0; i < patterns.size(); ++i) {
        aho.AddVectorOfNums(patterns[i], i + 1);
    }
    aho.Init();
    auto ahoAnswer = aho.FindPosPatterns(text);
    auto answer = WeakAlgo(patterns, text);

    std::sort(answer.begin(), answer.end());
    std::sort(ahoAnswer.begin(), ahoAnswer.end());
    ASSERT_EQ(answer.size(), ahoAnswer.size());
    for (size_t i = 0; i < answer.size(); ++i) {
        ASSERT_EQ(answer[i].first, ahoAnswer[i].first);
        ASSERT_EQ(answer[i].second, ahoAnswer[i].second);
    }
    std::cout << ahoAnswer.size() << "\n";
}

TEST(Lab4Test, Benchmark) {
    std::vector<unsigned long long> text;
    const int countWords = 100000;
    const int countPatterns = 1000;
    std::vector<std::vector<unsigned long long >> patterns(countPatterns);
    for (size_t i = 0; i < countWords; ++i) {
        text.push_back(randomKey() % 2 + 1);
    }
    for (size_t i = 0; i < countPatterns; ++i) {
        auto sizePattern = randomKey() % 100 + 1;
        std::vector<unsigned long long> pattern;
        for (size_t j = 0; j < sizePattern; ++j) {
            pattern.push_back(randomKey() % 2 + 1);
        }
        patterns[i] = pattern;
    }
    TAho aho;
    for (size_t i = 0; i < patterns.size(); ++i) {
        aho.AddVectorOfNums(patterns[i], i + 1);
    }
    auto begin = std::chrono::high_resolution_clock::now();
    aho.Init();
    auto ahoAnswer = aho.FindPosPatterns(text);
    auto end = std::chrono::high_resolution_clock::now();
    auto ahoTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    begin = std::chrono::high_resolution_clock::now();
    auto answer = WeakAlgo(patterns, text);
    end = std::chrono::high_resolution_clock::now();
    auto weakTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    std::cout << "aho time: " << ahoTime << " ms\n";
    std::cout << "weak time " << weakTime << " ms\n";
}