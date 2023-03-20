#include "treap.h"


std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

TTreap::TNode::TNode (int key) {
    left = nullptr;
    right = nullptr;
    this->key = key;
    this->priority = rng();
}

TTreap::TNode* TTreap::Merge(TNode* treap1, TNode* treap2) {
    if (treap1 == nullptr) {
        return treap2;
    }
    if (treap2 == nullptr) {
        return treap1;
    }
    if (treap1->priority > treap2->priority) {
        treap1->right = Merge(treap1->right, treap2);
        return treap1;
    }
    treap2->left = Merge(treap1, treap2->left);
    return treap2;
}

void TTreap::Split(TNode* treap, int key, TNode*& treap1, TNode*& treap2) {
    if (treap == nullptr) {
        treap1 = nullptr;
        treap2 = nullptr;
        return;
    }
    if (key > treap->key) {
        Split(treap->right, key, treap->right, treap2);
        treap1 = treap;
    } else {
        Split(treap->left, key, treap1, treap->left);
        treap2 = treap;
    }
}

TTreap::TNode* TTreap::Find(int key) {
    return Find(root, key);
}

TTreap::TNode* TTreap::Find(TNode* ptr, int key) {
    if (ptr == nullptr) {
        return nullptr;
    }
    if (ptr->key == key) {
        return ptr;
    }
    if (ptr->key > key) {
        return Find(ptr->left, key); 
    }
    return Find(ptr->right, key);
}

void TTreap::Destroy() {
    Destroy(root);
}

void TTreap::Destroy(TNode*& node) {
    if (node != nullptr) {
        Destroy(node->left);
        Destroy(node->right);
        delete node;
    }
}

TTreap::TTreap() {
    root = nullptr;
}

TTreap::~TTreap() {
    Destroy();
}

void TTreap::Print() {
    std::cout << "root\n";
    Print(root, 0);
}

void TTreap::Print(TNode* ptr, size_t height) {
    if (ptr != nullptr) {
        for (size_t i = 0; i < height; ++i) {
            std::cout << "     ";
        }
        std::cout << ptr->key << " " << ptr->priority << '\n';
        Print(ptr->left, height + 1);
        Print(ptr->right, height + 1); 
    }
}

void TTreap::Insert(int key) {
    TNode* ltreap = nullptr;
    TNode* rtreap = nullptr;
    Split(root, key, ltreap, rtreap);
    auto* node = new TNode(key);
    root = Merge(Merge(ltreap, node), rtreap);
}

void TTreap::Erase(int key) {
    TNode* ltreap = nullptr;
    TNode* rtreap = nullptr;
    Split(root, key, ltreap, rtreap);
    auto* rtreapRoot = rtreap;
    if (rtreapRoot->key == key) {
        if (rtreapRoot->right == nullptr) {
            rtreapRoot = nullptr;
        } else {
            rtreapRoot = rtreapRoot->right;
        }
    } else {
        while (rtreap != nullptr) {
            if (rtreap->left != nullptr && rtreap->left->key == key) {
                if (rtreap->left->right == nullptr) {
                    rtreap->left = nullptr;
                } else {
                    rtreap->left = rtreap->left->right;
                }
            }
            rtreap = rtreap->left;
        }
    }
    root = Merge(ltreap, rtreapRoot);
}

bool TTreap::Exist(int key) {
    return Find(key) != nullptr;
}

bool TTreap::Empty() {
    return root == nullptr;
}

size_t TTreap::Size(TTreap::TNode* ptr) {
    if (ptr != nullptr) {
        return 1 + Size(ptr->left) + Size(ptr->right);
    }
    return 0;
}

size_t TTreap::Size() {
    if (root != nullptr) {
        return Size(root);
    }
    return 0;
}

void TTreap::Clear() {
    if (root != nullptr) {
        Destroy(root->left);
        Destroy(root->right);
        delete root;
    }
    root = nullptr;
}
