#ifndef AHO_HPP
#define AHO_HPP

#include <queue>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <sstream>

class TAho {

private:
    struct TNode {
        unsigned long long value;
        std::vector<unsigned long long> id;
        TNode* parent;
        TNode* fail;
        std::vector<size_t> size;
        std::unordered_map<unsigned long long, TNode*> go;
        bool isLeaf;
    };
    TNode* root;

    static void Destroy(TNode* node) {
        if (node != nullptr) {
            for (auto sons : node->go) {
                Destroy(sons.second);
            }
            delete node;
        }
    }

    TNode* GetFailPointerFromLastFail(TNode* node, unsigned long long num) {
        if (node->go[num] == nullptr) {
            if (node != root) {
                return GetFailPointerFromLastFail(node->fail, num);
            }
            return root;
        }
        return node->go[num];
    }

    TNode* GetFail(TNode* node, unsigned long long num) {
        if (node == root) {
            return root;
        }
        if (node->parent == root) {
            return root;
        }
        return GetFailPointerFromLastFail(node->parent->fail, num);
    }

    TNode* Next(TNode* node, unsigned long long num) {
        if (node == root) {
            if (node->go[num] != nullptr) {
                return node->go[num];
            }
            return node;
        }
        if (node->go[num] != nullptr) {
            return node->go[num];
        }
        return Next(node->fail, num);
    }

public:

    TAho() {
        root = new TNode;
    }

    ~TAho() {
        Destroy(root);
    }

    void AddVectorOfNums(std::vector<unsigned long long>& nums, unsigned long long pid) {
        auto *temp = root;
        for (auto num : nums) {
            if (temp->go[num] == nullptr) {
                temp->go[num] = new TNode;
                temp->go[num]->parent = temp;
                temp = temp->go[num];
                temp->value = num;
            } else {
                temp = temp->go[num];
            }
        }
        temp->isLeaf = true;
        temp->id.push_back(pid);
        temp->size.push_back(nums.size());

    }


    void Init() {
        std::queue <TNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            auto* node = queue.front();
            queue.pop();
            node->fail = GetFail(node, node->value);
            if (node != root && node->fail->isLeaf) {
                node->isLeaf = true;
                for (size_t i = 0; i < node->fail->size.size(); ++i) {
                    node->size.push_back(node->fail->size[i]);
                    node->id.push_back(node->fail->id[i]);
                }
            } else if (node != root && node->fail->fail != nullptr && node->fail->fail->isLeaf) {
                node->isLeaf = true;
                for (size_t i = 0; i < node->fail->fail->size.size(); ++i) {
                    node->size.push_back(node->fail->fail->size[i]);
                    node->id.push_back(node->fail->fail->id[i]);
                }
            }
            for (auto elem : node->go) {
                if (elem.second != nullptr) {
                    queue.push(elem.second);
                }
            }
        }
    }

    void AddToAnswer(std::vector <std::pair<unsigned long long, unsigned long long>>& answer, TNode* temp, unsigned long long pos) {
        if (temp->isLeaf && temp != root) {
            for (size_t i = 0; i < temp->size.size(); ++i) {
                answer.emplace_back(pos - temp->size[i], temp->id[i]);
            }
        }

    }

    std::vector <std::pair<unsigned long long, unsigned long long>> FindPosPatterns(const std::vector<unsigned long long >& nums) {
        std::vector <std::pair<unsigned long long, unsigned long long>> answer;
        auto* temp = root;
        unsigned long long pos = 0;
        for (const auto& num : nums) {
            AddToAnswer(answer, temp, pos);
            temp = Next(temp, num);
            pos++;
        }
        AddToAnswer(answer, temp, pos);
        return answer;
    }
};

#endif