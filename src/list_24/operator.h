#ifndef ALGORITHMS_OPERATOR_H
#define ALGORITHMS_OPERATOR_H

#include <map>

namespace Operator {
enum EOperators {
    ADDITION = 0,
    SUBTRACTION,
    DIVISION,
    MULTIPLICATION,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    EMPTY
};

constexpr unsigned OPERATORS_SIZE = 7;
const std::map<EOperators, char> operators{
    { ADDITION, '+' },
    { SUBTRACTION, '-' },
    { DIVISION, '/' },
    { MULTIPLICATION, '*' },
    { LEFT_BRACKET, '(' },
    { RIGHT_BRACKET, ')' },
    { EMPTY, '\0' },
};
const std::map<EOperators, unsigned short> priorities{
    { ADDITION, 0x01 },
    { SUBTRACTION, 0x01 },
    { DIVISION, 0x10 },
    { MULTIPLICATION, 0x10 },
    { LEFT_BRACKET, 0x00 },
    { RIGHT_BRACKET, 0x00 },
    { EMPTY, 0x11 },
};

typedef struct
{
    char value;
    enum EOperators id;
    unsigned short priority;
} TOperator;

void init(TOperator* array);

TOperator getByChar(char op);
}

#endif //ALGORITHMS_OPERATOR_H
