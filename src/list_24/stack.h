#ifndef ALGORITHMS_STACK_H
#define ALGORITHMS_STACK_H

typedef long long TStackElement;

typedef struct
{
    TStackElement* elements;
    int top;
} Stack;

void StackInit(Stack* p_stack);

void StackDestroy(Stack* p_stack);

int StackIsEmpty(Stack* p_stack);

void StackPush(Stack* p_stack, TStackElement element);

TStackElement StackPop(Stack* p_stack);

#endif //ALGORITHMS_STACK_H
