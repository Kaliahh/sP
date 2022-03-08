#include "polygon.hpp"
#include <iostream>
#include <vector>

/**
 * Code to test the understanding of special member functions and references.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */

polygon polygon_factory(size_t count){ return polygon(count); }

void draw_value(polygon) { std::cout << "passed-by-value\n"; }
void draw(const polygon&) { std::cout << "passed-by-const-reference\n"; }
void draw(polygon&) { std::cout << "passed-by-lvalue-reference\n"; }
void draw(polygon&&) { std::cout << "passed-by-rvalue-reference\n"; }

int main()
{
    std::string ruler(40, '-');
    // TODO: Replace "???" with your predictions: what gets printed after each line?
    //       Note that some statements may print more than one line.
    // TODO: After all "???" are gone, step through the program in debugger and check your answers against output.
    // TODO: Answer the additional questions below.
    {   // for example:
        std::cout << ruler << std::endl;
        polygon poly;
        // default-constructor
        // destructor
    }
    {
        std::cout << ruler << std::endl;
        polygon poly(1);
        // custom-constructor(1)
        // destructor
    }
    {
        std::cout << ruler << std::endl;
        polygon poly = 1;
        // custom-constructor(1)
        // destructor
    }
    {
        std::cout << ruler << std::endl;
        const polygon poly0;
        // default-constructor

        std::cout << ruler << std::endl;
        polygon poly1 = poly0;
        // copy-constructor

        std::cout << ruler << std::endl;
        polygon poly2 = polygon(2);
        // custom-constructor(2)

        std::cout << ruler << std::endl;
        polygon poly3{{1,2},{3,4},{5,6},{7,8}};
        // custom-constructor{point{1,2},point{3,4},point{5,6},point{7,8}}

        std::cout << ruler << std::endl;
        poly2 = poly1;
        // copy-assignment

        std::cout << ruler << std::endl;
        poly2 = polygon_factory(3);
        // custom-constructor(3)
        // move-assignment
        // destructor

        std::cout << ruler << std::endl;
        draw_value(poly0);
        // copy-constructor
        // pass-by-value
        // destructor

        std::cout << ruler << std::endl;
        draw(poly0);
        // pass-by-const-reference

        std::cout << ruler << std::endl;
        draw(poly1);
        // pass-by-lvalue-reference

        std::cout << ruler << std::endl;
        draw(polygon_factory(4));
        // custom-constructor(4)
        // pass-by-rvalue-reference
        // destructor

        std::cout << ruler << std::endl;
        std::vector<polygon> polies(4, poly3);
        // copy-constructor
        // copy-constructor
        // copy-constructor
        // copy-constructor

        std::cout << ruler << std::endl;
        polies.push_back(poly3);
//        copy-constructor
//        move-constructor
//        destructor
//        move-constructor
//        destructor
//        move-constructor
//        destructor
//        move-constructor
//        destructor
        // TODO: Why are so many operations here?
        // Because everything has to be moved and the old vector deleted?

        std::cout << ruler << std::endl;
        polies.push_back(poly3);
        // copy-constructor
        // TODO: Why is the number of operations fewer here than for the above one?
        // Because it is cached?

        std::cout << ruler << std::endl;
        for (polygon p : polies)
            std::cout << p << " at " << &p << '\n';
        // copy-constructor, then the print, then the destructor, repeat.
        // TODO: Can we make the loop above more efficient?
        // Use a reference instead of a copy (add a '&' after polygon). Now no constructors or destructors are called
        // TODO: This is an incredibly common mistake, make sure to fix it, or ask.


        // We also get a bunch of destructor calls here, because we are leaving the scope.
    }
    {
        std::cout << ruler << std::endl;
//        draw(1);
        // customer-constructor(1)
        // passed-by-rvalue-reference
        // destructor
        // TODO: What is going on here? Why "1" is treated as polygon? This is unlikely to be intentional.
        // polygon has a constructor which takes an integer, and allows the compiler to implicitly convert an int
        // to a polygon
        // TODO: Can we forbid the last statement without breaking the previous code?
        // Add an 'explicit' before the constructor
        // TODO: Fix it in polygon.hpp so that this line does not compile.
    }
    {
        std::cout << ruler << std::endl;
        polygon poly = polygon(2);
        std::cout << poly << " at " << &poly << std::endl;
        draw_value(std::move(poly));
        // custom-constructor(2)
        // print
        // move-constructor
        // passed-by-value
        // destructor
        std::cout << poly << " at " << &poly << std::endl;
        // TODO: What was inside poly before draw_value call?
        // Two points
        // TODO: What is inside poly after draw_value call? Why?
        // Nothing. It was moved

        // destructor
    }
    {
        std::cout << ruler << std::endl;
        polygon poly = polygon(2);
        std::cout << poly << " at " << &poly << std::endl;
        draw(std::move(poly));
        // custom-constructor(2)
        // print
        // pass-by-rvalue-reference
        std::cout << poly << " at " << &poly << std::endl;
        // TODO: What was inside poly before draw call?
        // Two points
        // TODO: What is inside poly after draw call? Why?
        // Still two points. It was passed by reference.

        // destructor
    }
    std::cout << ruler << ruler << std::endl;
}
