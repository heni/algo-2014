#include <memory>
#include <iostream>

class TA {
    int* Internal;
public:
    TA(int* internal) 
        : Internal(internal)
    {}

    int GetState() const {
        return *Internal * 3;
    }
};

class TB {
    int* Internal;
public:
    TB(int* internal) 
        : Internal(internal)
    {}

    int GetState() const {
        return *Internal + 1;
    }
};

std::pair<TA, TB> CreateObjects() {
    std::unique_ptr<int> valptr(new int(10));
    return std::make_pair<TA, TB> (
        TA(valptr.get()),
        TB(valptr.get())
    );
}

int main() {
    std::pair<TA, TB> ab = CreateObjects();
    std::cout << "a:" << ab.first.GetState() << "; b:" << ab.second.GetState() << std::endl;
    return 0;
}
