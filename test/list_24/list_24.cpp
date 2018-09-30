#include "doctest.h"
#include <list_24/stack.h>

TEST_CASE("stack is created")
{
    Stack stack;
    StackInit(&stack);
    CHECK(stack.top == -1);
    CHECK(stack.elements == nullptr);
}

TEST_CASE("stack push works")
{
    TStackElement element = 10;
    Stack stack;
    StackInit(&stack);
    StackPush(&stack, element);
    CHECK(stack.top == 0);
    CHECK(stack.elements[stack.top] == element);
}

TEST_CASE("stack destroy works")
{
    TStackElement element = 10;
    Stack stack;
    StackInit(&stack);
    StackPush(&stack, element);
    CHECK(stack.top == 0);
    CHECK(stack.elements[stack.top] == element);
    StackDestroy(&stack);
    CHECK(stack.top == -1);
    CHECK(stack.elements == nullptr);
}

TEST_CASE("stack pop works")
{
    TStackElement element = 10;
    Stack stack;
    StackInit(&stack);
    StackPush(&stack, element);
    CHECK(stack.top == 0);
    CHECK(stack.elements[stack.top] == element);
    auto popped = StackPop(&stack);
    CHECK(popped == element);
    CHECK(stack.top == -1);
    CHECK(StackIsEmpty(&stack));
}
