#include "doctest.h"
#include "list_24/stack.h"

TEST_CASE("stack is created")
{
    Stack* p_stack = CreateStack();
    CHECK(p_stack->top == -1);
    CHECK(p_stack->elements == nullptr);
    StackDestroy(p_stack);
}

TEST_CASE("stack push works")
{
    TStackElement element = 10;
    Stack* p_stack = CreateStack();
    StackPush(p_stack, element);
    CHECK(p_stack->top == 0);
    CHECK(p_stack->elements[p_stack->top] == element);
    StackDestroy(p_stack);
}

TEST_CASE("stack destroy works")
{
    TStackElement element = 10;
    Stack* p_stack = CreateStack();
    StackPush(p_stack, element);
    CHECK(p_stack->top == 0);
    CHECK(p_stack->elements[p_stack->top] == element);
    StackDestroy(p_stack);
}

TEST_CASE("stack pop works")
{
    TStackElement element = 10;
    Stack* p_stack = CreateStack();
    StackPush(p_stack, element);
    CHECK(p_stack->top == 0);
    CHECK(p_stack->elements[p_stack->top] == element);
    auto popped = StackPop(p_stack);
    CHECK(popped == element);
    CHECK(p_stack->top == -1);
    CHECK(StackIsEmpty(p_stack));
    CHECK_THROWS(StackPop(p_stack));
    StackDestroy(p_stack);
}
