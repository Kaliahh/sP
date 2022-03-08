#include <iostream>
#include <vector>

//void print_v(std::vector<int> v) {
//    std::cout << "{";
//
//    for (auto it = std::begin(v); it != std::end(v); it++) {
//        if (std::next(it) == std::end(v)) {
//            std::cout <<  *it << "}" << std::endl;
//        }
//        else {
//            std::cout << *it << ", ";
//        }
//    }
//}

//std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
//    os << "{";
//
//    for (auto it = std::begin(v); it != std::end(v); it++) {
//        if (std::next(it) == std::end(v)) {
//            os <<  *it << "}";
//        }
//        else {
//            os << *it << ", ";
//        }
//    }
//}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << "{";

    for (auto it = std::begin(v); it != std::end(v); it++) {
        if (std::next(it) == std::end(v)) {
            os <<  *it << "}";
        }
        else {
            os << *it << ", ";
        }
    }
    return os;
}

int main() {
//    print_v(std::vector{1,2,3});
    std::cout << std::vector{1,2,3} << std::endl;
    std::cout << std::vector{1.2,2.3,3.4} << std::endl;
    std::cout << std::vector{std::vector{"Hello", "There"}, std::vector{"World"}} << std::endl;
    return 0;
}
