#include <algorithm>
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

char* Calculator::parse(char* pExpression)
{
    char* pBuffer = static_cast<char*>(calloc(STRING_LENGTH, sizeof(char)));
    if (pBuffer == nullptr) {
        throw "Cannot allocate memory";
    }
    char current;
    unsigned int k = 0;
    unsigned int i = 0;
    Operator::TOperator prevOperator;
    Operator::TOperator currentOperator;
    Stack* pStack = CreateStack();
    Operator::TOperator operators[OPERATORS_SIZE];
    create(operators);

    while (pExpression[k] != EOLN) {
        const bool isMinusSign = pExpression[k] == operators[SUBTRACTION].value;
        const bool isPlusSign = pExpression[k] == operators[ADDITION].value;
        const bool isPrevLeftBracket = k > 0 && pExpression[k - 1] == operators[LEFT_BRACKET].value;
        const bool isLeftBracket = pExpression[k] == operators[LEFT_BRACKET].value;
        const bool isValidUnarySign = k == 0 || isPrevLeftBracket;
        if (isValidUnarySign && (isMinusSign || isPlusSign)) {
            if (isMinusSign) {
                StackPush(pStack, std::string{ operators[UNARY_MINUS].value }.data());
            } else {
                StackPush(pStack, std::string{ operators[UNARY_PLUS].value }.data());
            }
        } else if (isOperator(pExpression[k]) || isLeftBracket) {
            if (!StackIsEmpty(pStack)) {
                current = StackPop(pStack)[0];
                prevOperator = getByChar(current);
                currentOperator = getByChar(pExpression[k]);
                bool isPrevPriorityHigher = prevOperator.priority >= currentOperator.priority;
                if (currentOperator.associativity == Operator::RIGHT) {
                    isPrevPriorityHigher = prevOperator.priority > currentOperator.priority;
                }
                const bool isCurrentOpLeftBracket = currentOperator.value == operators[LEFT_BRACKET].value;
                if (isPrevPriorityHigher && !isCurrentOpLeftBracket) {
                    while (isPrevPriorityHigher) {
                        pBuffer[i++] = SPACE;
                        pBuffer[i++] = prevOperator.value;
                        pBuffer[i++] = SPACE;
                        auto isCurrentLeftBracket = current == operators[LEFT_BRACKET].value;
                        if (!StackIsEmpty(pStack) && !isCurrentLeftBracket) {
                            current = StackPop(pStack)[0];
                            prevOperator = getByChar(current);
                        } else {
                            break;
                        }
                        isPrevPriorityHigher = prevOperator.priority >= currentOperator.priority;
                        if (!isPrevPriorityHigher) {
                            StackPush(pStack, std::string{ prevOperator.value }.data());
                        }
                        if (currentOperator.associativity == Operator::RIGHT) {
                            isPrevPriorityHigher = prevOperator.priority > currentOperator.priority;
                        }
                    }
                } else {
                    StackPush(pStack, std::string{ current }.data());
                }
            }
            StackPush(pStack, std::string{ pExpression[k] }.data());
            pBuffer[i++] = SPACE;
        } else if (pExpression[k] == operators[RIGHT_BRACKET].value) {
            current = StackPop(pStack)[0];
            while (current != operators[LEFT_BRACKET].value) {
                pBuffer[i++] = SPACE;
                pBuffer[i++] = current;
                pBuffer[i++] = SPACE;
                current = StackPop(pStack)[0];
            }
        } else if (pExpression[k] != SPACE) {
            pBuffer[i++] = pExpression[k];
        }
        k++;
    }

    while (!StackIsEmpty(pStack)) {
        pBuffer[i++] = SPACE;
        pBuffer[i++] = StackPop(pStack)[0];
    }

    StackDestroy(pStack);
    toUniqueSpaces(pBuffer);
    return pBuffer;
}

std::string Calculator::trim(const std::string& str)
{
    std::string buffer = str;
    buffer.erase(std::remove(buffer.begin(), buffer.end(), SPACE), buffer.end());
    return buffer;
}

void Calculator::isValidChar(char ch)
{
    auto isValidChar = std::isdigit(ch);
    if (!isValidChar) {
        throw std::logic_error("Error: " + std::string({ ch }) + " in not a digit");
    }
}

void Calculator::toUniqueSpaces(char* pExpression)
{
    std::string input(pExpression);
    std::string output;
    std::unique_copy(input.begin(), input.end(), std::back_insert_iterator<std::string>(output),
        [](char a, char b) { return std::isspace(a) && std::isspace(b); });
    strcpy(pExpression, output.data());
}
