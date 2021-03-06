#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <tuple>
#include <queue>
#include <set>
using namespace std;
typedef TGraph<int, bool> TTestGraph;

TTestGraph GraphFromFile(const string& filename) {
    ifstream in(filename.c_str());
    size_t n = 0, m = 0;
    in >> n >> m;
    TTestGraph result;
    for (size_t i = 1; i <= n; ++i) {
        result.AddVertex(i);
    }
    for (size_t i = 0; i < m; ++i) {
        int a , b;
        in >> a >> b;
        if (!(0 < a && a <= n && 0 < b && b <= n))
            throw runtime_error("bad edge: " + to_string(a) + "«—»" + to_string(b));
        result.AddEdge(a, b);
        result.AddEdge(b, a);
    }
    return std::move(result);   
}

void PrintComponents(const TTestGraph& g) {
    queue<int> q;
    set<int> was;
    size_t componentId = 0;
    TTestGraph::TVertexIterator vIt, vItEnd;
    for (std::tie(vIt, vItEnd) = g.GetVertices(); vIt != vItEnd; ++vIt) {
        if (! was.count(*vIt)) {
            cout << "component[" << ++componentId << "]: ";
            q.push(*vIt);
            was.insert(*vIt);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                cout << v << " ";
                TTestGraph::TConstEdgeIterator eIt, eItEnd;
                for (std::tie(eIt, eItEnd) = g.GetVertexAdjacency(v); eIt != eItEnd; ++eIt) {
                    if (! was.count(eIt->Destination)) {
                        q.push(eIt->Destination);
                        was.insert(eIt->Destination);
                    }
                }
            }
            cout << endl;
        }
    }
}

int main() {
    TTestGraph g = GraphFromFile("graph.data");
    PrintComponents(g);
    return 0;
};
