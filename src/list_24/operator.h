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
    EMPTY
};

constexpr unsigned OPERATORS_SIZE = 8;
const std::map<EOperators, char> operators{
    { ADDITION, '+' },
    { SUBTRACTION, '-' },
    { UNARY_MINUS, '~' },
    { DIVISION, '/' },
    { MULTIPLICATION, '*' },
    { LEFT_BRACKET, '(' },
    { RIGHT_BRACKET, ')' },
    { EMPTY, '\0' },
};
const std::map<EOperators, unsigned short> priorities{
    { ADDITION, 1 },
    { SUBTRACTION, 1 },
    { DIVISION, 2 },
    { MULTIPLICATION, 2 },
    { LEFT_BRACKET, 0 },
    { RIGHT_BRACKET, 0 },
    { UNARY_MINUS, 3 },
    { EMPTY, 4 },
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
