#include <memory>
#include <iostream>

class TA {
    std::shared_ptr<int> Internal;
public:
    TA(const std::shared_ptr<int>& internal) 
        : Internal(internal)
    {}

    int GetState() const {
        return *Internal * 3;
    }
};

class TB {
    std::shared_ptr<int> Internal;
public:
    TB(int* internal) 
        : Internal(internal)
    {}

    int GetState() const {
        return *Internal + 1;
    }
};

std::pair<TA, TB> CreateObjects() {
    std::shared_ptr<int> valptr = std::make_shared<int>(10);
    return std::make_pair<TA, TB> (
        valptr, 
        valptr.get()
    );
}

int main() {
    std::pair<TA, TB> ab = CreateObjects();
    std::cout << "a:" << ab.first.GetState() << "; b:" << ab.second.GetState() << std::endl;
    return 0;
}
