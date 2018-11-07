#include <cstring>
#include <malloc.h>
#include <stdexcept>
#include <utility>

#include "stack.h"

const Stack::TStack& Stack::create()
{
    const auto stack = new TStack();
    stack->elements = nullptr;
    stack->top = -1;
    return *stack;
}

void Stack::destroy(const TStack& stack)
{
    delete[] stack.elements;
    // TODO: fix crash
    // delete &stack;
}

int Stack::isEmpty(const TStack& stack)
{
    return stack.top < 0;
}

void Stack::push(TStack& stack, const TElement& element)
{
    const std::size_t elementSize = sizeof(element) / sizeof(char);
    char* buffer = static_cast<TElement>(malloc(sizeof(TElement) * elementSize));
    strcpy(buffer, element);
    stack.top++;
    if (stack.elements == nullptr) {
        stack.elements = static_cast<TElement*>(malloc(sizeof(TElement) * (stack.top + 1)));
    } else {
        stack.elements = static_cast<TElement*>(
            realloc(
                stack.elements,
                sizeof(TElement) * (stack.top + 1)));
    }
    if (stack.elements == nullptr) {
        throw std::runtime_error("Cannot allocate memory");
    }
    stack.elements[stack.top] = buffer;
}

Stack::TElement Stack::pop(TStack& stack)
{
    if (isEmpty(stack)) {
        throw std::logic_error("Cannot pop from empty stack");
    }
    const auto element = stack.elements[stack.top--];
    if (stack.top + 1 <= 0) {
        stack.elements = nullptr;
    } else {
        stack.elements = static_cast<TElement*>(
            realloc(
                stack.elements,
                sizeof(TElement) * (stack.top + 1)));
    }
    return element;
}
