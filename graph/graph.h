#include <map>

template<class TVertex, class TEdgeProperty> 
class TGraph {
    typedef std::map<TVertex, TEdgeProperty> TAdjacencyList;
    typedef std::map<TVertex, TAdjacencyList> TAdjacencyData;
    TAdjacencyData Adjacencies;

public:
    class TVertexIterator {
        typename TAdjacencyData::const_iterator InternalIt;
    public:
        TVertexIterator() {}
        TVertexIterator(typename TAdjacencyData::const_iterator it)
            : InternalIt(it) {}
        ~TVertexIterator() {}
        const TVertex& operator*() const {
            return InternalIt->first;
        }
        TVertexIterator& operator++() {
            ++InternalIt;
            return *this;
        }
        bool operator==(const TVertexIterator& rhs) const {
            return InternalIt == rhs.InternalIt;
        }
        bool operator!=(const TVertexIterator& rhs) const {
            return InternalIt != rhs.InternalIt;
        }
    };

    struct TEdge {
        const TVertex& Source;
        const TVertex& Destination;
        const TEdgeProperty& Property;
        TEdge(const TVertex& source, const TVertex& dest, const TEdgeProperty& props)
            : Source(source), Destination(dest), Property(props)
        {}
    };

    class TEdgeIterator {
        const TVertex* Source;
        typename TAdjacencyList::const_iterator InternalIt;
    public:
        TEdgeIterator() {}
        TEdgeIterator(const TVertex src, typename TAdjacencyList::const_iterator it)
            : Source(&src), InternalIt(it) {}
        ~TEdgeIterator() {}
        TEdge operator*() const {
            return TEdge(*Source, InternalIt->first, InternalIt->second);
        }
        TEdgeIterator& operator++() {
            ++InternalIt;
            return *this;
        }
        bool operator==(const TEdgeIterator& rhs) const {
            return InternalIt == rhs.InternalIt;
        }
        bool operator!=(const TEdgeIterator& rhs) const {
            return InternalIt != rhs.InternalIt;
        }
    };

    TGraph() {}
    ~TGraph() {}

    std::pair<TVertexIterator, TVertexIterator> GetVertices() const {
        return std::make_pair(TVertexIterator(Adjacencies.begin()), TVertexIterator(Adjacencies.end()));
    }
    std::pair<TEdgeIterator, TEdgeIterator> GetVertexAdjacency(const TVertex& v) const {
        typename TAdjacencyData::const_iterator it = Adjacencies.find(v);
        return std::make_pair(
            TEdgeIterator(it->first, it->second.begin()), 
            TEdgeIterator(it->first, it->second.end())
        );
    }

    bool HasVertex(const TVertex& v) {
        return Adjacencies.count(v);
    }

    void AddEdge(const TVertex& a, const TVertex& b, const TEdgeProperty& props) {
        AddVertex(a);
        AddVertex(b);
        Adjacencies[a][b] = props;
    }

    void AddVertex(const TVertex& v) {
        if (!HasVertex(v))
            Adjacencies[v] = TAdjacencyList();
    }
};
