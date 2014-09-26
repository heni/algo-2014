#include <algorithm>
#include <map>
#include <vector>
#include <iostream>


template <class TNode, class TPrior>
class TPriorityQueue {
    std::vector<std::pair<TNode, TPrior>> Nodes;
    std::map<TNode, size_t> Index;
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
        size_t i = Index[node];
        if (Nodes[i].second < nprior)
            throw std::runtime_error("bad priority");
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


int main() {
    std::vector<std::pair<int, double>> data(17);
    std::generate(
        data.begin(), data.end(), 
        []() -> decltype(data)::value_type {
            static int index = 1;
            return std::make_pair(++index, (index * index + index * 15) % 23);
        }
    );
    TPriorityQueue<int, double> q(data);

    while (!q.Empty()) {
        int node; double prior;
        std::tie(node, prior) = q.GetMin();
        std::cout << "(" << node << "," << prior << ") ";
        q.ExtractMin();
    }
    std::cout << std::endl;
    return 0;
}
