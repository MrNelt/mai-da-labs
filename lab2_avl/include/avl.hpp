#ifndef AVL_H
#define AVL_H


#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class TAVlTree {
    private:
    struct TNode {
        std::string key;
        unsigned long long value;
        int height;
        TNode* left;
        TNode* right;
        TNode(std::string& key, unsigned long long value) {
            this->key = key;
            this->value = value;
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };

    TNode* root;

    int Height(TNode* node) {
        return node != nullptr ? node->height : 0;
    }

    int BFactor(TNode* node) {
        return Height(node->right) - Height(node->left);
    }

    void FixHeight(TNode* node) {
        int hLeft = Height(node->left);
        int hRight = Height(node->right);
        node->height = std::max(hLeft, hRight) + 1;
    }

    TNode* RotateRight(TNode* node) {
        TNode* temp = node->left;
        node->left = temp->right;
        temp->right = node;
        FixHeight(temp);
        FixHeight(node);
        return temp;
    }

    TNode* RotateLeft(TNode* node) {
        TNode* temp = node->right;
        node->right = temp->left;
        temp->left = node;
        FixHeight(temp);
        FixHeight(node);
        return temp;
    }

    TNode* Balance(TNode* node) {
        FixHeight(node);

        if(BFactor(node) == 2) {
            if(BFactor(node->right) < 0) {
                node->right = RotateRight(node->right);
            }
            return RotateLeft(node);
        }

        if(BFactor(node) == -2 ) {
            if(BFactor(node->left) > 0 ) {
                node->left = RotateLeft(node->left);
            }
            return RotateRight(node);
        }
        return node;
    }

    TNode* Insert(TNode* node, std::string& key, unsigned long long value) {
        if (node == nullptr) {
            return new TNode(key, value);
        }
        if(key < node->key) {
            node->left = Insert(node->left, key, value);
        }
        else {
            node->right = Insert(node->right, key, value);
        }
        return Balance(node);
    }

    TNode* Find(TNode* node, std::string& key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->key == key) {
            return node;
        }
        if (key > node->key) {
            return Find(node->right, key);
        }
        return Find(node->left, key);
    }

    TNode* FindMin(TNode* node) {
        if (node->left == nullptr) {
            return node;
        }
        return FindMin(node->left);
    }

    TNode* RemoveMin(TNode* node) {
        if (node->left == nullptr) {
            return node->right;
        }
        node->left = RemoveMin(node->left);
        return Balance(node);
    }

    TNode* Erase(TNode* node, std::string& key) // удаление ключа k из дерева p
    {
        if (node == nullptr) {
            return nullptr;
        }
    
        if (key < node->key) {
            node->left = Erase(node->left, key);
        }
        else if(key > node->key) {
            node->right = Erase(node->right, key);	
        }
        else {
            TNode* left = node->left;
            TNode* right = node->right;
            delete node;
            if(right == nullptr) {
                 return left;
            }
            TNode* min = FindMin(right);
            min->right = RemoveMin(right);
            min->left = left;
            return Balance(min);
        }
        return Balance(node);
    }

    void Destroy(TNode*& node) {
        if (node != nullptr) {
            Destroy(node->left);
            Destroy(node->right);
            delete node;
        }
    }

    void Destroy() {
        Destroy(root);
    }

    size_t Size(TNode* node) {
        if (node != nullptr) {
            return 1 + Size(node->left) + Size(node->right);
        }
        return 0;
    }

    size_t HeightTree(TNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    void SaveToFile(std::ofstream& file, TNode* node) {
        if (node == nullptr) {
            return;
        }
        auto keyf = node->key;
        auto valuef = node->value;
        auto sizeKeyf = keyf.size();
        file.write(reinterpret_cast<char*>(&sizeKeyf), sizeof(unsigned long long));
        for (char & symb : keyf) {
            file.write(reinterpret_cast<char*>(&symb), sizeof(char));
        }
        file.write(reinterpret_cast<char*>(&valuef), sizeof(unsigned long long));
        SaveToFile(file, node->left);
        SaveToFile(file, node->right);
    }

    public:

    TAVlTree() {
        root = nullptr;
    }

    ~TAVlTree() {
        Destroy();
    }

    void Insert(std::string& key, unsigned long long value) {
        root = Insert(root, key, value);
    }

    void Erase(std::string& key) {
        root = Erase(root, key);
    }

    std::pair<unsigned long long, bool> Exist(std::string& key) {
        TNode* node = Find(root, key);
        if (node != nullptr) {
            return {node->value, true};
        }
        return {0, false};

    }

    size_t Size() {
        return Size(root);
    }

    void Clear() {
        if (root != nullptr) {
            Destroy(root->left);
            Destroy(root->right);
            delete root;
        }
        root = nullptr;
    }

    bool Empty() {
        return root == nullptr;
    }

    size_t HeightTree() {
        return HeightTree(root);
    }

    void SaveToFile(std::ofstream& file) {
        SaveToFile(file, root);
    }

    void LoadFromFile(std::ifstream& file) {

        Clear();
        unsigned long long size;
        file.read(reinterpret_cast<char *>(&size), sizeof(unsigned long long));
        for (size_t i = 0; i < size; ++i) {
            std::string key;
            unsigned long long value;
            size_t keySize;
            file.read(reinterpret_cast<char*>(&keySize), sizeof(unsigned long long));
            for (size_t i = 0; i < keySize; ++i) {
                char symb;
                file.read(reinterpret_cast<char*>(&symb), sizeof(char));
                key += symb;
            }
            file.read(reinterpret_cast<char *>(&value), sizeof(unsigned long long));
            Insert(key, value);
        }
    }
};
#endif