#include <sstream>

template<class T>
T from_string(const std::string& source) {
    std::stringstream ss(source);
    T result;
    ss >> result;
    return result;
}

template<class T>
std::string to_string(const T& source) {
    std::stringstream ss;
    ss << source;
    return ss.str();
}

std::string string_plus (const std::string& a, const std::string& b) {
    return to_string(from_string<long long>(a) + from_string<long long>(b));
}


