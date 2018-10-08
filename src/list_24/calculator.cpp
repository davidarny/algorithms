#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <string.h>

#include "calculator.h"
#include "operator.h"
#include "stack.h"

using namespace Operator;
using namespace Calculator;

long long Calculator::calculate(const char* p_expression)
{
    Stack* p_stack = CreateStack();
    unsigned i = 0;
    unsigned j = 0;
    long long buffer = 0;
    auto* p_numbers = static_cast<long long*>(calloc(NUM_OF_STRINGS, sizeof(long long)));
    if (p_numbers == nullptr) {
        throw std::runtime_error("Cannot allocate memory");
    }
    char* p_ch;
    char* p_buffer = static_cast<char*>(calloc(STRING_LENGTH, sizeof(char)));
    if (p_buffer == nullptr) {
        throw std::runtime_error("Cannot allocate memory");
    }

    strcat(p_buffer, p_expression);

    p_ch = strtok(p_buffer, "*-+/() ");
    while (p_ch != nullptr) {
        p_numbers[j++] = strtoll(p_ch, nullptr, 10);
        p_ch = strtok(nullptr, "*-+/() ");
    }
    j = 0;

    while (p_expression[i] != '\0') {
        if (check(p_expression[i])) {
            if (p_expression[i] == operators.at(ADDITION)) {
                StackPush(p_stack, StackPop(p_stack) + StackPop(p_stack));
            } else if (p_expression[i] == operators.at(MULTIPLICATION)) {
                StackPush(p_stack, StackPop(p_stack) * StackPop(p_stack));
            } else if (p_expression[i] == operators.at(DIVISION)) {
                buffer = StackPop(p_stack);
                if (buffer != 0) {
                    StackPush(p_stack, StackPop(p_stack) / buffer);
                } else {
                    free(p_buffer);
                    free(p_numbers);
                    throw "Dividing by 0";
                }
            } else if (p_expression[i] == operators.at(SUBTRACTION)) {
                buffer = StackPop(p_stack);
                StackPush(p_stack, StackPop(p_stack) - buffer);
            }
        } else if (p_expression[i] != ' ') {
            StackPush(p_stack, p_numbers[j]);
            i += floor(log10(llabs(p_numbers[j])));
            j++;
        }
        i++;
    }

    free(p_buffer);
    free(p_numbers);
    buffer = StackPop(p_stack);
    StackDestroy(p_stack);

    return buffer;
}

bool Calculator::check(char op)
{
    return op == operators.at(ADDITION)
        || op == operators.at(SUBTRACTION)
        || op == operators.at(MULTIPLICATION)
        || op == operators.at(DIVISION);
}

char* Calculator::toPostfix(char* p_expression)
{
    char* p_buffer = static_cast<char*>(calloc(STRING_LENGTH, sizeof(char)));
    if (p_buffer == nullptr) {
        throw "Cannot allocate memory";
    }
    char temp;
    unsigned int k = 0;
    unsigned int i = 0;
    Operator::TOperator lastOperator;
    Operator::TOperator currentOperator;
    Stack* p_stack = CreateStack();
    Operator::TOperator operators[OPERATORS_SIZE];
    create(operators);

    while (p_expression[k] != '\0') {
        if (check(p_expression[k]) || p_expression[k] == operators[LEFT_BRACKET].value) {
            if (p_stack->top != -1) {
                temp = static_cast<char>(StackPop(p_stack));
                lastOperator = getByChar(temp);
                currentOperator = getByChar(p_expression[k]);
                if (lastOperator.priority >= currentOperator.priority
                    && currentOperator.value != operators[LEFT_BRACKET].value) {
                    while (lastOperator.priority >= currentOperator.priority) {
                        p_buffer[i++] = ' ';
                        p_buffer[i++] = lastOperator.value;
                        p_buffer[i++] = ' ';
                        if (p_stack->top != -1) {
                            temp = static_cast<char>(StackPop(p_stack));
                            lastOperator = getByChar(temp);
                            if (temp == operators[LEFT_BRACKET].value)
                                StackPush(p_stack, temp);
                        } else {
                            break;
                        }
                    }
                } else {
                    StackPush(p_stack, temp);
                }
            }
            StackPush(p_stack, static_cast<long long>(p_expression[k]));
            p_buffer[i++] = ' ';
        } else if (p_expression[k] == operators[RIGHT_BRACKET].value) {
            temp = static_cast<char>(StackPop(p_stack));
            while (temp != operators[LEFT_BRACKET].value) {
                p_buffer[i++] = ' ';
                p_buffer[i++] = temp;
                p_buffer[i++] = ' ';
                temp = static_cast<char>(StackPop(p_stack));
            }
        } else if (p_expression[k] != ' ') {
            p_buffer[i++] = p_expression[k];
        }
        k++;
    }

    while (p_stack->top != -1) {
        p_buffer[i++] = ' ';
        p_buffer[i++] = static_cast<char>(StackPop(p_stack));
        p_buffer[i++] = ' ';
    }

    StackDestroy(p_stack);
    return p_buffer;
}

std::string Calculator::trim(const std::string& str)
{
    std::string buffer = str;
    buffer.erase(std::remove(buffer.begin(), buffer.end(), ' '), buffer.end());
    return buffer;
}
