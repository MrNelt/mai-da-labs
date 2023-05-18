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

    void Print(TNode* node, std::vector<unsigned long long> stack) {
        if (node != nullptr) {
            if (node != root) {
                stack.push_back(node->value);
            }
            for (auto elem : node->go) {
                if (elem.second != nullptr) {
                    Print(elem.second, stack);
                }
            }
            if (node->isLeaf) {
                for (auto pid : node->id) {
                    for (auto num: stack) {
                        std::cout << num << " ";
                    }
                    std::cout << "ID: " << pid << "\n";
                }
            }
        }
    }

public:

    TAho() {
        root = new TNode;
    }

    ~TAho() {
        Destroy(root);
    }
    void Print() {
        std::vector <unsigned long long > stack;
        Print(root, stack);
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


int main() {
    TAho aho;
    std::string line;
    std::getline(std::cin, line);
    unsigned long long pid = 0;
    while (!line.empty()) {
        pid++;
        unsigned long long num;
        auto stream = std::istringstream(line);
        std::vector<unsigned long long > nums;
        while (stream >> num) {
            nums.push_back(num);
        }
        aho.AddVectorOfNums(nums, pid);
        std::getline(std::cin, line);
    }
    aho.Init();
    std::vector<std::pair<unsigned long, unsigned long long>> info;
    std::vector<unsigned long long > text;

    unsigned long long page = 0;
    unsigned long long num = 0;
    line = "";
    while (std::getline(std::cin, line)) {
        page++;
        auto stream = std::istringstream(line);
        num = 0;
        unsigned long long elem;
        while (stream >> elem) {
            num++;
            text.push_back(elem);
            info.emplace_back(page, num);
        }
    }
    auto answers = aho.FindPosPatterns(text);
    for (auto answer : answers) {
        std::cout << info[answer.first].first << ", " << info[answer.first].second << ", " << answer.second << "\n";
    }
}