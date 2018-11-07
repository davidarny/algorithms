#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <stdexcept>
#include <string.h>

#include "calculator.h"
#include "operator.h"
#include "stack.h"

using namespace Operator;
using namespace Calculator;
using namespace Stack;

bool Calculator::isOperator(char op)
{
    return op == operators.at(ADDITION)
        || op == operators.at(SUBTRACTION)
        || op == operators.at(MULTIPLICATION)
        || op == operators.at(DIVISION)
        || op == operators.at(UNARY_MINUS)
        || op == operators.at(UNARY_PLUS)
        || op == operators.at(POWER);
}

char* Calculator::parse(char* expression)
{
    char* buffer = static_cast<char*>(calloc(STRING_LENGTH, sizeof(char)));
    if (buffer == nullptr) {
        throw "Cannot allocate memory";
    }
    char current;
    unsigned int cycleIndex = 0;
    unsigned int bufferIndex = 0;
    TOperator prevOperator;
    TOperator currentOperator;
    auto stack = create();
    TOperator operators[OPERATORS_SIZE];
    create(operators);

    while (expression[cycleIndex] != EOLN) {
        const char ch = expression[cycleIndex];
        const bool isMinusSign = ch == operators[SUBTRACTION].value;
        const bool isPlusSign = ch == operators[ADDITION].value;
        const bool isPrevLeftBracket = cycleIndex > 0 && expression[cycleIndex - 1] == operators[LEFT_BRACKET].value;
        const bool isLeftBracket = ch == operators[LEFT_BRACKET].value;
        const bool isValidUnarySign = cycleIndex == 0 || isPrevLeftBracket;
        if (isValidUnarySign && (isMinusSign || isPlusSign)) {
            if (isMinusSign) {
                push(stack, std::string{ operators[UNARY_MINUS].value }.data());
            } else {
                push(stack, std::string{ operators[UNARY_PLUS].value }.data());
            }
        } else if (isOperator(ch) || isLeftBracket) {
            if (!isEmpty(stack)) {
                current = *pop(stack);
                prevOperator = getByChar(current);
                currentOperator = getByChar(ch);
                bool isPrevPriorityHigher = prevOperator.priority >= currentOperator.priority;
                if (currentOperator.associativity == RIGHT) {
                    isPrevPriorityHigher = prevOperator.priority > currentOperator.priority;
                }
                const bool isCurrentOpLeftBracket = currentOperator.value == operators[LEFT_BRACKET].value;
                if (isPrevPriorityHigher && !isCurrentOpLeftBracket) {
                    while (isPrevPriorityHigher) {
                        buffer[bufferIndex++] = SPACE;
                        buffer[bufferIndex++] = prevOperator.value;
                        buffer[bufferIndex++] = SPACE;
                        const auto isCurrentLeftBracket = current == operators[LEFT_BRACKET].value;
                        if (!isEmpty(stack) && !isCurrentLeftBracket) {
                            current = *pop(stack);
                            prevOperator = getByChar(current);
                        } else {
                            break;
                        }
                        isPrevPriorityHigher = prevOperator.priority >= currentOperator.priority;
                        if (!isPrevPriorityHigher) {
                            push(stack, std::string{ prevOperator.value }.data());
                        }
                        if (currentOperator.associativity == RIGHT) {
                            isPrevPriorityHigher = prevOperator.priority > currentOperator.priority;
                        }
                    }
                } else {
                    push(stack, std::string{ current }.data());
                }
            }
            push(stack, std::string{ ch }.data());
            buffer[bufferIndex++] = SPACE;
        } else if (ch == operators[RIGHT_BRACKET].value) {
            current = *pop(stack);
            while (current != operators[LEFT_BRACKET].value) {
                buffer[bufferIndex++] = SPACE;
                buffer[bufferIndex++] = current;
                buffer[bufferIndex++] = SPACE;
                current = *pop(stack);
            }
        } else if (ch != SPACE) {
            buffer[bufferIndex++] = ch;
        }
        cycleIndex++;
    }

    while (!isEmpty(stack)) {
        buffer[bufferIndex++] = SPACE;
        buffer[bufferIndex++] = *pop(stack);
    }

    destroy(stack);
    trimAll(buffer);

    return buffer;
}

std::string Calculator::trim(const std::string& str)
{
    std::string buffer = str;
    buffer.erase(std::remove(buffer.begin(), buffer.end(), SPACE), buffer.end());
    return buffer;
}

void Calculator::trimAll(char* expression)
{
    const std::string input(expression);
    std::string output;
    const auto onCopy = [](char a, char b) {
        return std::isspace(a) && std::isspace(b);
    };
    std::unique_copy(
        input.begin(),
        input.end(),
        std::back_insert_iterator<std::string>(output),
        onCopy);
    boost::trim(output);
    strcpy(expression, output.data());
}
