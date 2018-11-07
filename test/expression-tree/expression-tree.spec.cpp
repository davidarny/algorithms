#include <string>

#include "doctest.h"
#include "expression-tree/Tree.h"
#include "expression-tree/calculator.h"

TEST_CASE("expression-tree works")
{
    std::string line = "a + b";
    const auto postfix = Calculator::parse(line.data());
    CHECK_NOTHROW(Tree::construct(postfix));
}

TEST_CASE("works with unary signs")
{
    std::string line = "a ^ (-b + c) * (d - (+e))";
    const auto postfix = Calculator::parse(line.data());
    CHECK_NOTHROW(Tree::construct(postfix));
}
