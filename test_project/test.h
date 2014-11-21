#pragma once
#include "structure.h"
#include <iostream>

template <class T>
class Test {
public:
    bool operator()() const;
};

template<>
bool Test<int>::operator()() const {
    std::shared_ptr<TStack<int>> stack = TStack<int>::Create(0);
    for (size_t i = 1; i < 10; ++i)
        stack = stack->AddElement(i);
    while (stack) {
        std::shared_ptr<TStack<int>> node = stack;
        stack = stack->Pop();
        std::cout << node->Data << std::endl;
    }
    return true;
};
