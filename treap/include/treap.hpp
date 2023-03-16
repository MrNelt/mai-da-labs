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
        int key;
        unsigned long long priority;

        TNode (int key);
    };

    TNode* root;

    TNode* Merge(TNode* treap1, TNode* treap2);

    void Split(TNode* treap, int key, TNode*& treap1, TNode*& treap2);

    static void Print(TNode* ptr, size_t height);

    TNode* Find(int key);

    TNode* Find(TNode* ptr, int key);

    void Destroy(TNode* node);

    public:

    TTreap();

    ~TTreap();

    void Print();

    void Destroy();

    void Insert(int key);

    void Erase(int key);

    bool Exist(int key);

};

#endif