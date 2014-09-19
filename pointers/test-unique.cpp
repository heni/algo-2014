#include <memory>
#include <iostream>

void print_value(int* ptr) {
    std::cout << *ptr << std::endl;
}

void print_value(std::unique_ptr<int>& ptr) {
    std::cout << *ptr << std::endl;
}

void test_01() {
    std::unique_ptr<int> ptr(new int(10));
    print_value(ptr.get());
    print_value(ptr);
}

void test_02() {
    int* p = new int(20);
    std::unique_ptr<int> ptr(p);
    print_value(ptr.get());
    ptr.reset(new int(25));
    print_value(ptr.get());

    std::unique_ptr<int> ptr2 = std::move(ptr);
    print_value(ptr2.get());
}

void test_03() {
    std::auto_ptr<int> ptr(new int(30));
    print_value(ptr.get());
    std::auto_ptr<int> ptr2 = ptr;
    print_value(ptr2.get());
}

int main() {
    test_01();
    test_02();
    test_03();
    return 0;
}
