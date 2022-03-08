#include <iostream>
#include <vector>

using namespace std;


// Difference between struct and class:
// Struct members are public by default
// Class members are private by default

struct DefaultTest {

    int a;

    // Default constructor
    DefaultTest() = default;

    // Default destructor
    ~DefaultTest() = default;

    // Default copy-constructor
    DefaultTest(const DefaultTest& other) = default;

    // Default copy-assignment
    DefaultTest& operator=(const DefaultTest& other) = default;

    // Default move-constructor
    DefaultTest(DefaultTest&& other) = default;

    // Default move-assignment
    DefaultTest& operator=(DefaultTest&& other) = default;


    void operator-(DefaultTest& u, int b) {

    }
};

class CustomTest {
public:
    int a;

    CustomTest() {
        a = 3;
    }

    ~CustomTest() {
        a = 0;
    }

    CustomTest(const CustomTest& other) {
//        a = other.a;
        *this = other; // Reuse copy-assignment
    }

    CustomTest& operator=(const CustomTest& other) {
        a = other.a * 2;
        return *this;
    }

    CustomTest(CustomTest&& other) noexcept {
        *this = std::move(other); // Reuse move-assignment
    }

    CustomTest& operator=(CustomTest&& other) noexcept {
        if (this == &other) { // Guard against self-assignment
            return *this;
        }
        std::swap(a, other.a);
        return *this;
    }
};

void operator+(DefaultTest& a, int b) {
    a.a += b;
}

void operator+(int a, DefaultTest& b) {
    b + a;
}

int main() {

    DefaultTest defaultTest{};

    cout << "Default " << defaultTest.a << endl;

    4 + defaultTest;

    cout << "Default " << defaultTest.a << endl;

    return 0;
}
