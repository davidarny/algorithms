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

    p_ch = strtok(p_buffer, Operator::join().data());
    while (p_ch != nullptr) {
        p_numbers[j++] = strtoll(p_ch, nullptr, 10);
        p_ch = strtok(nullptr, Operator::join().data());
    }
    j = 0;

    while (p_expression[i] != EOLN) {
        if (check(p_expression[i])) {
            if (p_expression[i] == operators.at(POWER)) {
                StackPush(p_stack, static_cast<int>(std::pow(StackPop(p_stack), StackPop(p_stack))));
            } else if (p_expression[i] == operators.at(UNARY_MINUS)) {
                StackPush(p_stack, -StackPop(p_stack));
            } else if (p_expression[i] == operators.at(ADDITION)) {
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
        } else if (p_expression[i] != SPACE) {
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
        || op == operators.at(DIVISION)
        || op == operators.at(UNARY_MINUS)
        || op == operators.at(POWER);
}

char* Calculator::parse(char* p_expression)
{
    char* p_buffer = static_cast<char*>(calloc(STRING_LENGTH, sizeof(char)));
    if (p_buffer == nullptr) {
        throw "Cannot allocate memory";
    }
    char currentChar;
    unsigned int k = 0;
    unsigned int i = 0;
    Operator::TOperator prevOperator;
    Operator::TOperator currentOperator;
    Stack* p_stack = CreateStack();
    Operator::TOperator operators[OPERATORS_SIZE];
    create(operators);

    while (p_expression[k] != EOLN) {
        const bool isMinusSign = p_expression[k] == operators[SUBTRACTION].value;
        const bool isPrevLeftBracket = k > 0 && p_expression[k - 1] == operators[LEFT_BRACKET].value;
        const bool isLeftBracket = p_expression[k] == operators[LEFT_BRACKET].value;
        const bool isValidUnaryMinus = k == 0 || isPrevLeftBracket;
        if (isMinusSign && isValidUnaryMinus) {
            StackPush(p_stack, operators[UNARY_MINUS].value);
        } else if (check(p_expression[k]) || isLeftBracket) {
            if (!StackIsEmpty(p_stack)) {
                currentChar = static_cast<char>(StackPop(p_stack));
                prevOperator = getByChar(currentChar);
                currentOperator = getByChar(p_expression[k]);
                bool isPrevPriorityHigher = prevOperator.priority >= currentOperator.priority;
                if (currentOperator.associativity == Operator::RIGHT) {
                    isPrevPriorityHigher = prevOperator.priority > currentOperator.priority;
                }
                const bool isCurrentOpLeftBracket = currentOperator.value == operators[LEFT_BRACKET].value;
                if (isPrevPriorityHigher && !isCurrentOpLeftBracket) {
                    while (isPrevPriorityHigher) {
                        p_buffer[i++] = SPACE;
                        p_buffer[i++] = prevOperator.value;
                        p_buffer[i++] = SPACE;
                        auto isCurrentLeftBracket = currentChar == operators[LEFT_BRACKET].value;
                        if (!StackIsEmpty(p_stack) && !isCurrentLeftBracket) {
                            currentChar = static_cast<char>(StackPop(p_stack));
                            prevOperator = getByChar(currentChar);
                        } else {
                            break;
                        }
                        isPrevPriorityHigher = prevOperator.priority >= currentOperator.priority;
                        if (!isPrevPriorityHigher) {
                            StackPush(p_stack, prevOperator.value);
                        }
                        if (currentOperator.associativity == Operator::RIGHT) {
                            isPrevPriorityHigher = prevOperator.priority > currentOperator.priority;
                        }
                    }
                } else {
                    StackPush(p_stack, currentChar);
                }
            }
            StackPush(p_stack, static_cast<long long>(p_expression[k]));
            p_buffer[i++] = SPACE;
        } else if (p_expression[k] == operators[RIGHT_BRACKET].value) {
            currentChar = static_cast<char>(StackPop(p_stack));
            while (currentChar != operators[LEFT_BRACKET].value) {
                p_buffer[i++] = SPACE;
                p_buffer[i++] = currentChar;
                p_buffer[i++] = SPACE;
                currentChar = static_cast<char>(StackPop(p_stack));
            }
        } else if (p_expression[k] != SPACE) {
            isValidChar(p_expression[k]);
            p_buffer[i++] = p_expression[k];
        }
        k++;
    }

    while (!StackIsEmpty(p_stack)) {
        p_buffer[i++] = SPACE;
        p_buffer[i++] = static_cast<char>(StackPop(p_stack));
    }

    StackDestroy(p_stack);
    unique_spaces(p_buffer);
    return p_buffer;
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

void Calculator::unique_spaces(char* str)
{
    std::string input(str);
    std::string output;
    std::unique_copy(input.begin(), input.end(), std::back_insert_iterator<std::string>(output),
        [](char a, char b) { return std::isspace(a) && std::isspace(b); });
    strcpy(str, output.data());
}
