#ifndef AVL_H
#define AVL_H


#include <algorithm>
#include <cstddef>
#include <fstream>

class TAVlTree {
    private:

    struct TNode {
        int key;
        int height;
        TNode* left;
        TNode* right;
        TNode(int key) {
            this->key = key;
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

    TNode* Insert(TNode* node, int key) {
        if (node == nullptr) {
            return new TNode(key);
        }
        if(key < node->key) {
            node->left = Insert(node->left, key);
        }
        else {
            node->right = Insert(node->right, key);
        }
        return Balance(node);
    }

    TNode* Find(TNode* node, int key) {
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

    TNode* Erase(TNode* node, int key) // удаление ключа k из дерева p
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
        return 1 + std::max(Height(node->left), Height(node->right));
    }

    void SaveToFile(std::ofstream& file, TNode* node) {
        if (node == nullptr) {
            return;
        }
        file << node->key << "\n";
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

    void Insert(int key) {
        root = Insert(root, key);
    }

    void Erase(int key) {
        root = Erase(root, key);
    }

    bool Exist(int key) {
        return Find(root, key) != nullptr;
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
        int key;
        while (file >> key) {
            Insert(key);
        }
    }
};

#endif