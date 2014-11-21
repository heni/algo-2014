#pragma once
#include <memory>

template<class T>
class Test;

template<class T>
class TStack: public std::enable_shared_from_this<TStack<T>> {
    typedef std::enable_shared_from_this<TStack<T>> TParent;
    std::shared_ptr<TStack<T>> Next;
    T Data;

    friend class Test<T>;
    
public:
    TStack(const T& data)
        : Next(nullptr)
        , Data(data)
    {}

    std::shared_ptr<TStack> AddElement(const T& data) {
        std::shared_ptr<TStack> nHead = std::make_shared<TStack>(data);
        nHead->Next = TParent::shared_from_this();
        return nHead;
    }

    static std::shared_ptr<TStack> Create(const T& data) {
        return std::make_shared<TStack>(data);
    }

    std::shared_ptr<TStack> Pop() {
        std::shared_ptr<TStack> nHead = Next;
        Next = nullptr;
        return nHead;
    }
//
//    const T& GetData() const {
//        return Data;
//    }
};
