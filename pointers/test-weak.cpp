#include <memory>
#include <iostream>

struct TA;

class TB {
    std::weak_ptr<TA> Parent;
public:
    TB(const std::shared_ptr<TA>& parent) 
        : Parent(parent)
    {}
    void PrintPointers() {
        std::shared_ptr<TA> parent = Parent.lock();
        std::cout << "created objects (from child):" << std::endl
            << "\tparent: " << parent.get() << std::endl
            << "\tchild: " << this << std::endl;
    }
    ~TB() {
        std::cout << "~TB()" << std::endl;
    }
};

struct TA {
    std::shared_ptr<TB> Child;
    TA() {}
    ~TA() {
        std::cout << "~TA()" << std::endl;
    }
};

int main() {
    std::shared_ptr<TA> ptr2parent = std::make_shared<TA>();
    std::shared_ptr<TB> ptr2child = std::make_shared<TB>(ptr2parent);
    ptr2parent->Child = ptr2child;
    std::cout << "created objects (from main):" << std::endl
        << "\tparent: " << ptr2parent.get() << std::endl
        << "\tchild: " << ptr2child.get() << std::endl;
    ptr2child->PrintPointers();
    return 0;
}
