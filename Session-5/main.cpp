#include <iostream>
#include <vector>
#include <memory>
#include <chrono>

#define ITERATIONS 100
#define ELEMENTS 10000000

class Base {
public:
    int a{0};

    virtual void increment() = 0;
    void decrement() {
        a--;
    }
};

class Derived : public Base {
    void increment() override {
        a++;
    }
};

std::vector<std::unique_ptr<Base>> vec(ELEMENTS);


int main() {

//    std::generate(vec.begin(), vec.end(), []() { return std::move(std::make_unique<Derived>()); });
//
//    for (int i = 0; i < ELEMENTS; i++) {
//        vec[i] = std::move(std::make_unique<Derived>());
//    }

    for (auto& elem : vec) {
        elem = std::move(std::make_unique<Derived>());
    }

    double sum_increment = 0;
    double sum_decrement = 0;

    for (int i = 0; i < ITERATIONS; i++) {
        auto first = std::chrono::high_resolution_clock::now();

        for (const auto& elem : vec) {
            elem->increment();
        }

        auto last = std::chrono::high_resolution_clock::now();

        sum_increment += std::chrono::duration<double, std::milli>(last - first).count();

        first = std::chrono::high_resolution_clock::now();

        for (const auto& elem : vec) {
            elem->decrement();
        }

        last = std::chrono::high_resolution_clock::now();

        sum_decrement += std::chrono::duration<double, std::milli>(last - first).count();
    }

    std::cout << "Increment: " << sum_increment / ITERATIONS << std::endl;
    std::cout << "Decrement: " << sum_decrement / ITERATIONS << std::endl;

    // ~4 millisekunder i forskel?

    return 0;
}
