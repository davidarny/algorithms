#ifndef ALGORITHMS_OPERATOR_H
#define ALGORITHMS_OPERATOR_H

#include <map>

namespace Operator {
enum EOperators {
    ADDITION = 0,
    SUBTRACTION,
    UNARY_MINUS,
    DIVISION,
    MULTIPLICATION,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    POWER,
    EMPTY
};

constexpr unsigned OPERATORS_SIZE = 9;
const std::map<EOperators, char> operators{
    { ADDITION, '+' },
    { SUBTRACTION, '-' },
    { UNARY_MINUS, '~' },
    { DIVISION, '/' },
    { MULTIPLICATION, '*' },
    { LEFT_BRACKET, '(' },
    { RIGHT_BRACKET, ')' },
    { POWER, '^' },
    { EMPTY, '\0' },
};
const std::map<EOperators, unsigned short> priorities{
    { LEFT_BRACKET, 0 },
    { RIGHT_BRACKET, 0 },
    { ADDITION, 1 },
    { SUBTRACTION, 1 },
    { DIVISION, 2 },
    { MULTIPLICATION, 2 },
    { POWER, 3 },
    { UNARY_MINUS, 4 },
    { EMPTY, 5 },
};

typedef struct
{
    char value;
    enum EOperators id;
    unsigned short priority;
} TOperator;

void create(TOperator* array);

TOperator getByChar(char op);
}

#endif //ALGORITHMS_OPERATOR_H
