#include <string.h>

#include "calculator/calculator.h"
#include "calculator/operator.h"
#include "calculator/stack.h"
#include "doctest.h"

TEST_CASE("stack is created")
{
    Stack* pStack = CreateStack();
    CHECK(pStack->top == -1);
    CHECK(pStack->elements == nullptr);
    StackDestroy(pStack);
}

TEST_CASE("stack push works")
{
    TStackElement element = 10;
    Stack* pStack = CreateStack();
    StackPush(pStack, element);
    CHECK(pStack->top == 0);
    CHECK(pStack->elements[pStack->top] == element);
    StackDestroy(pStack);
}

TEST_CASE("stack destroy works")
{
    TStackElement element = 10;
    Stack* pStack = CreateStack();
    StackPush(pStack, element);
    CHECK(pStack->top == 0);
    CHECK(pStack->elements[pStack->top] == element);
    StackDestroy(pStack);
}

TEST_CASE("stack pop works")
{
    TStackElement element = 10;
    Stack* pStack = CreateStack();
    StackPush(pStack, element);
    CHECK(pStack->top == 0);
    CHECK(pStack->elements[pStack->top] == element);
    auto popped = StackPop(pStack);
    CHECK(popped == element);
    CHECK(pStack->top == -1);
    CHECK(StackIsEmpty(pStack));
    CHECK_THROWS(StackPop(pStack));
    StackDestroy(pStack);
}

TEST_CASE("get operator by char")
{
    char ch = '+';
    auto op = Operator::getByChar(ch);
    CHECK(op.value == ch);
    CHECK(op.id == Operator::ADDITION);
    CHECK(op.priority == Operator::priorities.at(Operator::ADDITION));
    CHECK(op.associativity == Operator::LEFT);
    ch = '-';
    op = Operator::getByChar(ch);
    CHECK(op.value == ch);
    CHECK(op.id == Operator::SUBTRACTION);
    CHECK(op.priority == Operator::priorities.at(Operator::SUBTRACTION));
    CHECK(op.associativity == Operator::LEFT);
    ch = '/';
    op = Operator::getByChar(ch);
    CHECK(op.value == ch);
    CHECK(op.id == Operator::DIVISION);
    CHECK(op.priority == Operator::priorities.at(Operator::DIVISION));
    CHECK(op.associativity == Operator::LEFT);
    ch = '*';
    op = Operator::getByChar(ch);
    CHECK(op.value == ch);
    CHECK(op.id == Operator::MULTIPLICATION);
    CHECK(op.priority == Operator::priorities.at(Operator::MULTIPLICATION));
    CHECK(op.associativity == Operator::LEFT);
    ch = '(';
    op = Operator::getByChar(ch);
    CHECK(op.value == ch);
    CHECK(op.id == Operator::LEFT_BRACKET);
    CHECK(op.priority == Operator::priorities.at(Operator::LEFT_BRACKET));
    CHECK(op.associativity == Operator::LEFT);
    ch = ')';
    op = Operator::getByChar(ch);
    CHECK(op.value == ch);
    CHECK(op.id == Operator::RIGHT_BRACKET);
    CHECK(op.priority == Operator::priorities.at(Operator::RIGHT_BRACKET));
    CHECK(op.associativity == Operator::LEFT);
    ch = '~';
    op = Operator::getByChar(ch);
    CHECK(op.value == ch);
    CHECK(op.id == Operator::UNARY_MINUS);
    CHECK(op.priority == Operator::priorities.at(Operator::UNARY_MINUS));
    CHECK(op.associativity == Operator::LEFT);
    ch = '^';
    op = Operator::getByChar(ch);
    CHECK(op.value == ch);
    CHECK(op.id == Operator::POWER);
    CHECK(op.priority == Operator::priorities.at(Operator::POWER));
    CHECK(op.associativity == Operator::RIGHT);
    ch = '\0';
    op = Operator::getByChar(ch);
    CHECK(op.value == ch);
    CHECK(op.id == Operator::EMPTY);
    CHECK(op.priority == Operator::priorities.at(Operator::EMPTY));
    CHECK(op.associativity == Operator::LEFT);
}

TEST_CASE("operator join")
{
    auto joined = Operator::join();
    CHECK(joined.compare("+-~/*()^ ") == 0);
}

TEST_CASE("calculator parse")
{
    std::string input("2^3^2");
    std::string output(Calculator::parse(input.data()));
    CHECK(output.compare("2 3 2 ^ ^") == 0);
    input = "1+(18-6)/6 * (672 + 5) - 300 + (2^3^2)";
    output = Calculator::parse(input.data());
    CHECK(output.compare("1 18 6 - 6 / 672 5 + * + 300 - 2 3 2 ^ ^ +") == 0);
}

TEST_CASE("calculator calculate")
{
    std::string input("2 3 2 ^ ^");
    CHECK(Calculator::calculate(input.data()) == 512);
    input = "1 18 6 - 6 / 672 5 + * + 300 - 2 3 2 ^ ^ +";
    CHECK(Calculator::calculate(input.data()) == 1567);
}
