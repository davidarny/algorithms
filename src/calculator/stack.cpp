#include <malloc.h>
#include <stdexcept>

#include "stack.h"

Stack* CreateStack()
{
    auto* p_stack = new Stack();
    p_stack->elements = nullptr;
    p_stack->top = -1;
    return p_stack;
}

void StackDestroy(Stack* p_stack)
{
    delete[] p_stack->elements;
    delete p_stack;
}

int StackIsEmpty(Stack* p_stack)
{
    return p_stack->top < 0;
}

void StackPush(Stack* p_stack, TStackElement element)
{
    p_stack->top++;
    if (p_stack->elements == nullptr) {
        p_stack->elements = static_cast<TStackElement*>(malloc(sizeof(TStackElement) * (p_stack->top + 1)));
    } else {
        p_stack->elements = static_cast<TStackElement*>(realloc(
            p_stack->elements,
            sizeof(TStackElement) * (p_stack->top + 1)));
    }
    if (p_stack->elements == nullptr) {
        throw std::runtime_error("Cannot allocate memory");
    }
    p_stack->elements[p_stack->top] = element;
}

TStackElement StackPop(Stack* p_stack)
{
    if (StackIsEmpty(p_stack)) {
        throw std::logic_error("Cannot pop from empty stack");
    }
    auto element = p_stack->elements[p_stack->top--];
    if (p_stack->top + 1 <= 0) {
        p_stack->elements = nullptr;
    } else {
        p_stack->elements = static_cast<TStackElement*>(realloc(
            p_stack->elements,
            sizeof(TStackElement) * (p_stack->top + 1)));
    }
    return element;
}
