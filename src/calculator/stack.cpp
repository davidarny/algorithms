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

void StackDestroy(Stack* pStack)
{
    delete[] pStack->elements;
    delete pStack;
}

int StackIsEmpty(Stack* pStack)
{
    return pStack->top < 0;
}

void StackPush(Stack* pStack, TStackElement element)
{
    pStack->top++;
    if (pStack->elements == nullptr) {
        pStack->elements = static_cast<TStackElement*>(malloc(sizeof(TStackElement) * (pStack->top + 1)));
    } else {
        pStack->elements = static_cast<TStackElement*>(realloc(
            pStack->elements,
            sizeof(TStackElement) * (pStack->top + 1)));
    }
    if (pStack->elements == nullptr) {
        throw std::runtime_error("Cannot allocate memory");
    }
    pStack->elements[pStack->top] = element;
}

TStackElement StackPop(Stack* pStack)
{
    if (StackIsEmpty(pStack)) {
        throw std::logic_error("Cannot pop from empty stack");
    }
    auto element = pStack->elements[pStack->top--];
    if (pStack->top + 1 <= 0) {
        pStack->elements = nullptr;
    } else {
        pStack->elements = static_cast<TStackElement*>(realloc(
            pStack->elements,
            sizeof(TStackElement) * (pStack->top + 1)));
    }
    return element;
}
