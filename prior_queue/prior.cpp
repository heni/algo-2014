#include <algorithm>
#include <map>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <chrono>
#include <limits>
#include <cassert>


template <class TNode, class TPrior, class TIndexType=std::map<TNode, size_t>>
class TPriorityQueue {
    std::vector<std::pair<TNode, TPrior>> Nodes;
    TIndexType Index;
    size_t Size;
    
    static size_t Parent(size_t i) { return (i - 1) / 2; }
    static size_t LeftChild(size_t i) { return 2 * i + 1; }
    static size_t RightChild(size_t i) { return 2 * i + 2; }

    bool IsBetter(size_t l, size_t r) const {
        return Nodes[l].second < Nodes[r].second;
    }

    void Swap(size_t a, size_t b) {
        std::swap(Nodes[a], Nodes[b]);
        Index[Nodes[a].first] = a;
        Index[Nodes[b].first] = b;
    }
    
    void HeapUp(size_t i) {
        for (size_t p = Parent(i); i && IsBetter(i, p); p = Parent(i)) {
            Swap(i, p);
            i = p;
        }
    }

    void HeapDown(size_t i) {
        for (size_t ch = LeftChild(i); ch < Size; ch = LeftChild(i)) {
            if (ch + 1 < Size && IsBetter(ch + 1, ch))
                ++ch;
            if (IsBetter(i, ch))
                return;
            Swap(i, ch);
            i = ch;
        }
    }

    void BuildHeap() {
        for (size_t i = Size / 2; i; --i)
            HeapDown(i - 1);
    }
public:
    TPriorityQueue():Size(0) {}
    TPriorityQueue(const std::vector<std::pair<TNode, TPrior>>& items)
        : Size(items.size())
        , Nodes(items)
    {
        for (size_t i = 0; i < Size; ++i) {
            Index[Nodes[i].first] = i;
        }
        BuildHeap();
    }

    void Add(const TNode& node, const TPrior& prior) {
        Index[node] = Size;
        Nodes.push_back(std::make_pair(node, prior));
        HeapUp(Size++);
    }

    const std::pair<TNode, TPrior>& GetMin() const {
        return Nodes.front();
    }

    void ExtractMin() {
        Index.erase(Nodes[0].first);
        Nodes[0] = Nodes.back();
        Nodes.pop_back();
        --Size;
        Index[Nodes[0].first] = 0;
        HeapDown(0);
    }

    void Update(const TNode& node, const TPrior& nprior) {
        typename TIndexType::const_iterator it = Index.find(node);
        if (it == Index.end())
            throw std::runtime_error("no such node");
        const size_t i = it->second;
        if (Nodes[i].second < nprior)
            throw std::runtime_error("bad priority");
        Nodes[i].second = nprior;
        HeapUp(i);
    }

    bool Empty() const {
        return !Size;
    }

    void Print() const {
        for (size_t i = 0; i < Size; ++i)
            std::cout << "(" << Nodes[i].first << "," << Nodes[i].second << ") ";
        std::cout << std::endl;
    }
};

template<class TPriorityQueue>
void test(const std::vector<std::pair<int, double>>& data, 
          std::function<double(int)> priorFn, std::function<double(int)> priorFn2) {
    auto start_time = std::chrono::steady_clock::now();
    TPriorityQueue q(data);
    for(size_t i = 1; i <= data.size() / 2; ++i) {
        if (priorFn(i) > priorFn2(i)) {
            //std::cout << i << std::endl;
            q.Update(i, priorFn2(i));
        }
    }
    double previous = -std::numeric_limits<double>::infinity();
    while (!q.Empty()) {
        int node; double prior;
        std::tie(node, prior) = q.GetMin();
        assert(prior >= previous);
        previous = prior;
        q.ExtractMin();
    }
    auto end_time = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count() << std::endl;
}

int main() {
    std::function<double(int)> priorFn = [](int i)->double { 
        return (i * i + i * 15) % 23671; 
    };
    std::function<double(int)> priorFn2 = [](int i)->double { 
        return (i * 7) % 23671; 
    };

    std::vector<size_t> tests = {100, 1000, 100000, 10000000};
    for (size_t testSize: tests) {
        std::vector<std::pair<int, double>> data(testSize);
        size_t index = 0;
        std::generate(
            data.begin(), data.end(), 
            [&priorFn, &index]() -> decltype(data)::value_type {
                ++index;
                return std::make_pair(index, priorFn(index));
            }
        );
        std::cout << "test size: " << testSize << std::endl;
        test<TPriorityQueue<int, double, std::map<int, size_t>>>(data, priorFn, priorFn2);
        test<TPriorityQueue<int, double, std::unordered_map<int, size_t>>>(data, priorFn, priorFn2);
    }
    return 0;
}
