#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <tuple>
#include <queue>
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
            throw runtime_error("bad edge");
        result.AddEdge(a, b, true);
        result.AddEdge(b, a, true);
    }
    return std::move(result);   
}

void PrintComponents(const TTestGraph& g) {
    queue<int> q;
    map<int, bool> was;
    size_t componentId = 0;
    TTestGraph::TVertexIterator vIt, vItEnd;
    for (std::tie(vIt, vItEnd) = g.GetVertices(); vIt != vItEnd; ++vIt) {
        if (! was.count(*vIt)) {
            cout << "component[" << ++componentId << "]: ";
            q.push(*vIt);
            was[*vIt] = true;
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                cout << v << " ";
                TTestGraph::TEdgeIterator eIt, eItEnd;
                for (std::tie(eIt, eItEnd) = g.GetVertexAdjacency(v); eIt != eItEnd; ++eIt) {
                    const TTestGraph::TEdge edge = *eIt;
                    if (! was.count(edge.Destination)) {
                        q.push(edge.Destination);
                        was[edge.Destination] = true;
                    }
                }
            }
            cout << endl;
        }
    }
}

int main() {
    const TTestGraph g = GraphFromFile("graph.data");
    PrintComponents(g);
    return 0;
};
