#include <memory>
#include <iostream>

struct TA;

class TB {
    std::shared_ptr<TA> Parent;
public:
    TB(const std::shared_ptr<TA>& parent) 
        : Parent(parent)
    {}
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
    std::cout << "created objects:" << std::endl
        << "\tparent: " << ptr2parent.get() << std::endl
        << "\tchild: " << ptr2child.get() << std::endl;
    return 0;
}
