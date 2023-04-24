#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <chrono>


std::mt19937 randomKey(std::chrono::steady_clock::now().time_since_epoch().count());

int main() {
    std::string path;
    std::cin >> path;
    std::ofstream file(path);
    size_t const countActions = 1000;

    std::vector <std::pair<std::string, unsigned long long>> data;
    for (size_t i = 0; i < countActions; ++i) {
        std::string key = std::to_string(static_cast<int>(randomKey()));
        auto value = randomKey();
        data.emplace_back(key, value);
    }
    for (size_t i = 0; i < countActions; ++i) {
        file << "+" << " " << data[i].first << " " << data[i].second << "\n";
    }
    for (size_t i = 0; i < countActions; ++i) {
        file << "-" << " " << data[i].first << "\n";
    }
}
