#include <chrono>
#include <random>
#include <iostream>
#include <algorithm>


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

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

TTreap::TNode::TNode (std::string key, unsigned long long value) {
    left = nullptr;
    right = nullptr;
    this->key = std::move(key);
    this->value = value;
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

void TTreap::Split(TNode* treap, const std::string& key, TNode*& treap1, TNode*& treap2) {
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

TTreap::TNode* TTreap::Find(const std::string& key) {
    return Find(root, key);
}

TTreap::TNode* TTreap::Find(TNode* ptr, const std::string& key) {
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

void TTreap::Insert(const std::string& key, unsigned long long value) {
    TNode* ltreap = nullptr;
    TNode* rtreap = nullptr;
    Split(root, key, ltreap, rtreap);
    auto* node = new TNode(key, value);
    root = Merge(Merge(ltreap, node), rtreap);
}

void TTreap::Erase(const std::string& key) {
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

std::pair<unsigned long long, bool> TTreap::Exist(const std::string& key) {
    auto *node = Find(key);
    if (node == nullptr) {
        return {0, false};
    }
    return {node->value, true};
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

size_t TTreap::Height(TTreap::TNode* ptr) {
    if (ptr != nullptr) {
        return 1 + std::max(Height(ptr->left), Height(ptr->right));
    }
    return 0;
}

size_t TTreap::Height() {
    return Height(root);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    TTreap treap;
    std::string command;
    while (std::cin >> command) {
        if (command == "+") {
            std::string key;
            unsigned long long value;
            std::cin >> key >> value;
            std::transform(key.begin(), key.end(), key.begin(),
                           [](unsigned char symb){ return std::tolower(symb); });
            if (treap.Exist(key).second) {
                std::cout << "Exist\n";
            } else {
                treap.Insert(key, value);
                std::cout << "OK\n";
            }
        }
        else if (command == "-") {
            std::string key;
            std::cin >> key;
            std::transform(key.begin(), key.end(), key.begin(),
                           [](unsigned char symb){ return std::tolower(symb); });
            if (!treap.Exist(key).second) {
                std::cout << "NoSuchWord\n";
            } else {
                treap.Erase(key);
                std::cout << "OK\n";
            }
        } else {
            std::transform(command.begin(), command.end(), command.begin(),
                           [](unsigned char symb){ return std::tolower(symb); });
            auto node = treap.Exist(command);
            if (node.second) {
                std::cout << "OK: " << node.first << "\n";
            } else {
                std::cout << "NoSuchWord\n";
            }
        }
    }
}
