#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <unordered_map>

class TSortOp {
    std::function<int()> RandomGenerator;
    mutable std::unordered_map<int, int> Keys;
public:
    TSortOp():
        RandomGenerator(std::default_random_engine(
            std::chrono::system_clock::now().time_since_epoch().count()
        ))
    {}

    bool operator() (int a, int b) const {
        if (!Keys.count(a))
            Keys[a] = RandomGenerator();
        if (!Keys.count(b))
            Keys[b] = RandomGenerator();
        return Keys[a] < Keys[b];
    }
};


void test_not_lambda() {
    std::vector<int> data;
    for (size_t i = 0;i < 100; ++i) 
        data.push_back(i);
    std::sort(data.begin(), data.end(), TSortOp());
    for (int v: data) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

void test_lambda() {
    std::vector<int> data;
    for (size_t i = 0;i < 100; ++i) 
        data.push_back(i);
    auto random_generator = std::default_random_engine();
    std::unordered_map<int, int> random_cache;

    std::function<bool(int,int)> comparator = [&](int a, int b) {
        if (!random_cache.count(a))
            random_cache[a] = random_generator();
        if (!random_cache.count(b))
            random_cache[b] = random_generator();
        return random_cache[a] < random_cache[b];
    };
    std::sort(data.begin(), data.end(), comparator);
    for (int v: data) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

int main() {
    test_not_lambda();
    test_lambda();
    return 0;
}
