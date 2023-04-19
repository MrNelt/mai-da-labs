#ifndef TREAP_H
#define TREAP_H

#include <chrono>
#include <cstddef>
#include <random>
#include <iostream>


class TTreap {

private:

    struct TNode {
        TNode* left;
        TNode* right;
        std::string key;
        unsigned long long value;
        unsigned long long priority;

        TNode (std::string key, unsigned long long value);
    };

    TNode* root;

    TNode* Merge(TNode* treap1, TNode* treap2);

    void Split(TNode* treap, const std::string& key, TNode*& treap1, TNode*& treap2);

    static void Print(TNode* ptr, size_t height);

    TNode* Find(const std::string& key);

    TNode* Find(TNode* ptr, const std::string& key);

    size_t Size(TNode* ptr);

    size_t Height(TNode* ptr);

    void Destroy(TNode*& node);

    void Destroy();

public:

    TTreap();

    ~TTreap();

    void Print();

    void Insert(const std::string& key, unsigned long long value);

    void Erase(const std::string& key);

    std::pair<unsigned long long, bool> Exist(const std::string& key);

    bool Empty();

    void Clear();

    size_t Height();

    size_t Size();

};

#endif