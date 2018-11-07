#ifndef ALGORITHMS_STACK_H
#define ALGORITHMS_STACK_H

#include <string>

typedef char* TStackElement;

typedef struct
{
    TStackElement* elements;
    int top;
} Stack;

Stack* CreateStack();

void StackDestroy(Stack* pStack);

int StackIsEmpty(Stack* pStack);

void StackPush(Stack* pStack, TStackElement element);

TStackElement StackPop(Stack* pStack);

#endif //ALGORITHMS_STACK_H
