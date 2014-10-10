#include "string_plus.hpp"

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(testSimple1) {
    BOOST_CHECK_EQUAL(string_plus(string("11"), string("11")), string("22"));
}

BOOST_AUTO_TEST_CASE(testSimple2) {
    BOOST_CHECK_EQUAL(string_plus(string("11"), string("-11")), string("0"));
}

BOOST_AUTO_TEST_CASE(testSimple3) {
    BOOST_CHECK_EQUAL(string_plus(string("0"), string("23")), string("23"));
}

BOOST_AUTO_TEST_CASE(testSimple4) {
    BOOST_CHECK_EQUAL(string_plus(string("-11"), string("-11")), string("-22"));
}

template<long long N>
void complex_test() {
    string result("0");
    for (size_t i = 1; i <= N; ++i) 
        result = string_plus(result, to_string(i));
    BOOST_CHECK_EQUAL(result, to_string(N * (N+1) / 2));
}

BOOST_AUTO_TEST_CASE(testManyComplex) {
    complex_test<10>();
    complex_test<20>();
    complex_test<100>();
    complex_test<10000>();
    complex_test<1000000>();
}

void test_from_file(const string& filename) {
    ifstream in(filename.c_str());
    BOOST_REQUIRE_MESSAGE(in, "can't open file: " + filename);
    string a, b, c;
    in >> a >> b >> c;
    BOOST_REQUIRE_MESSAGE(in, "bad format in file: " + filename);
    BOOST_CHECK_MESSAGE(
        string_plus(a, b) == c, 
        "//can't complete test from file '" + filename + "', expected: " + c + " got: " + string_plus(a, b)
    );
}

BOOST_AUTO_TEST_CASE(testFromFile) {
    test_from_file("test-01.txt");
    test_from_file("test-02.txt");
    test_from_file("test-03.txt");
    test_from_file("test-04.txt");
}
