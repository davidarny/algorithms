#ifndef ALGORITHMS_STACK_H
#define ALGORITHMS_STACK_H

#include <string>

namespace Stack {
typedef char* TElement;
typedef struct
{
    TElement* elements;
    int top;
} TStack;

const TStack& create();

void destroy(const TStack& stack);

int isEmpty(const TStack& stack);

void push(TStack& stack, const TElement& element);

TElement pop(TStack& stack);
}

#endif //ALGORITHMS_STACK_H
