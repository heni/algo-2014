#pragma once
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

    template <class _TEdgeProperty>
    class _TEdge {
        _TEdgeProperty* PropsPtr;
    public:
        TVertex Source;
        TVertex Destination;
        _TEdge()
            : PropsPtr(nullptr)
        {}

        _TEdge(const TVertex& source, const TVertex& dest, _TEdgeProperty& props)
            : Source(source), Destination(dest), PropsPtr(&props)
        {}

        _TEdgeProperty& GetProperty() {
            return *PropsPtr;
        }

        const _TEdgeProperty& GetProperty() const {
            return *PropsPtr;
        }
    };
    typedef _TEdge<TEdgeProperty> TEdge;
    typedef _TEdge<const TEdgeProperty> TConstEdge;

    template <class TInternalIterator, class TEdge>
    class _TEdgeIterator {
        typedef _TEdgeIterator<TInternalIterator, TEdge> TMe;

        const TVertex* Source;
        TInternalIterator InternalIt;
        /*small hack:
            store precomputed TEdge inside iterator memory
            be carefull - this data may be invalidated after iterator incrementation
        */
        mutable TEdge InternalEdge;
        mutable bool IsInitialized;

        void ForceInitialization() const {
            if (!IsInitialized) {
                InternalEdge = TEdge(*Source, InternalIt->first, InternalIt->second);
                IsInitialized = true;
            }
        }
        void ResetInitialization() {
            IsInitialized = false;
        }
    public:
        _TEdgeIterator() 
            : IsInitialized(false) 
        {}

        _TEdgeIterator(const TVertex& src, TInternalIterator it)
            : Source(&src), InternalIt(it), IsInitialized(false)
        {}

        _TEdgeIterator(const TMe& rhs)
            : Source(rhs.Source), InternalIt(rhs.InternalIt), IsInitialized(false)
        {}

        _TEdgeIterator& operator=(const TMe& rhs) {
            if (this == &rhs)
                return *this;
            Source = rhs.Source;
            InternalIt = rhs.InternalIt;
            IsInitialized = false;
            return *this;
        }

        ~_TEdgeIterator() {}

        TEdge& operator*() const {
            ForceInitialization();
            return InternalEdge;
        }

        TEdge* operator->() const {
            ForceInitialization();
            return &InternalEdge;
        }

        TMe& operator++() {
            ++InternalIt;
            ResetInitialization();
            return *this;
        }

        bool operator==(const TMe& rhs) const {
            return InternalIt == rhs.InternalIt;
        }

        bool operator!=(const TMe& rhs) const {
            return InternalIt != rhs.InternalIt;
        }
    };
    typedef _TEdgeIterator<typename TAdjacencyList::iterator, TEdge> TEdgeIterator;
    typedef _TEdgeIterator<typename TAdjacencyList::const_iterator, TConstEdge> TConstEdgeIterator;

    TGraph() {}
    ~TGraph() {}

    std::pair<TVertexIterator, TVertexIterator> GetVertices() const {
        return std::make_pair(TVertexIterator(Adjacencies.begin()), TVertexIterator(Adjacencies.end()));
    }

    std::pair<TConstEdgeIterator, TConstEdgeIterator> GetVertexAdjacency(const TVertex& v) const {
        typename TAdjacencyData::const_iterator it = Adjacencies.find(v);
        return std::make_pair(
            TConstEdgeIterator(it->first, it->second.begin()), 
            TConstEdgeIterator(it->first, it->second.end())
        );
    }

    std::pair<TEdgeIterator, TEdgeIterator> GetVertexAdjacency(const TVertex& v) {
        typename TAdjacencyData::iterator it = Adjacencies.find(v);
        return std::make_pair(
            TEdgeIterator(it->first, it->second.begin()), 
            TEdgeIterator(it->first, it->second.end())
        );
    }

    bool HasVertex(const TVertex& v) {
        return Adjacencies.count(v);
    }

    void AddEdge(const TVertex& a, const TVertex& b, const TEdgeProperty& props = TEdgeProperty()) {
        AddVertex(a);
        AddVertex(b);
        Adjacencies[a][b] = props;
    }

    void AddVertex(const TVertex& v) {
        if (!HasVertex(v))
            Adjacencies[v] = TAdjacencyList();
    }
};
