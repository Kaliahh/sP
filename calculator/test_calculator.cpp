#include "calculator.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>


TEST_CASE("Calculate expressions")
{
    auto sys = calculator::symbol_table_t{};
    auto a = sys.new_var("a", 2);
    auto b = sys.new_var("b", 3);
    auto c = sys.new_var("c");
    auto state = sys.new_state();

    SUBCASE("Reading the value of a variable from state")
    {
        // check initial values:
        CHECK(a(state) == 2);
        CHECK(b(state) == 3);
        CHECK(c(state) == 0);
    }
    SUBCASE("Evaluation of addition and subtraction")
    {
        CHECK((a+b)(state) == 5);
        CHECK((a-b)(state) == -1);
        // the state should not have changed:
        CHECK(a(state) == 2);
        CHECK(b(state) == 3);
        CHECK(c(state) == 0);
        CHECK(-a(state) == -2);
        CHECK(+b(state) == 3);
    }
    SUBCASE("Assignment expression evaluation")
    {
        CHECK(c(state) == 0);
        CHECK((c <<= b - a)(state) == 1);
        CHECK(c(state) == 1);
    }

    SUBCASE("Evaluation of multiplication and division")
    {
        CHECK((a*b)(state) == 6);
        CHECK((a/b)(state) == 2./3);
        CHECK((b/a)(state) == 3./2);
        CHECK_THROWS_MESSAGE((a/c)(state), "division by zero");
    }
}
