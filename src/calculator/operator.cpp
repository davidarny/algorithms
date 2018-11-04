#include "operator.h"

using namespace Operator;

void Operator::create(TOperator array[OPERATORS_SIZE])
{
    TOperator addition;
    addition.value = operators.at(ADDITION);
    addition.id = ADDITION;
    addition.priority = priorities.at(ADDITION);
    addition.associativity = LEFT;
    array[ADDITION] = addition;

    TOperator subtraction;
    subtraction.value = operators.at(SUBTRACTION);
    subtraction.id = SUBTRACTION;
    subtraction.priority = priorities.at(SUBTRACTION);
    subtraction.associativity = LEFT;
    array[SUBTRACTION] = subtraction;

    TOperator division;
    division.value = operators.at(DIVISION);
    division.id = DIVISION;
    division.priority = priorities.at(DIVISION);
    division.associativity = LEFT;
    array[DIVISION] = division;

    TOperator multiplication;
    multiplication.value = operators.at(MULTIPLICATION);
    multiplication.id = MULTIPLICATION;
    multiplication.priority = priorities.at(MULTIPLICATION);
    multiplication.associativity = LEFT;
    array[MULTIPLICATION] = multiplication;

    TOperator leftBracket;
    leftBracket.value = operators.at(LEFT_BRACKET);
    leftBracket.id = LEFT_BRACKET;
    leftBracket.priority = priorities.at(LEFT_BRACKET);
    leftBracket.associativity = LEFT;
    array[LEFT_BRACKET] = leftBracket;

    TOperator rightBracket;
    rightBracket.value = operators.at(RIGHT_BRACKET);
    rightBracket.id = RIGHT_BRACKET;
    rightBracket.priority = priorities.at(RIGHT_BRACKET);
    rightBracket.associativity = LEFT;
    array[RIGHT_BRACKET] = rightBracket;

    TOperator unaryMinus;
    unaryMinus.value = operators.at(UNARY_MINUS);
    unaryMinus.id = UNARY_MINUS;
    unaryMinus.priority = priorities.at(UNARY_MINUS);
    unaryMinus.associativity = LEFT;
    array[UNARY_MINUS] = unaryMinus;

    TOperator empty;
    empty.value = operators.at(EMPTY);
    empty.id = EMPTY;
    empty.priority = priorities.at(EMPTY);
    empty.associativity = LEFT;
    array[EMPTY] = empty;

    TOperator power;
    power.value = '^';
    power.id = POWER;
    power.priority = priorities.at(POWER);
    power.associativity = RIGHT;
    array[POWER] = power;
}

TOperator Operator::getByChar(char op)
{
    TOperator result;
    TOperator array[OPERATORS_SIZE];
    create(array);

    switch (op) {
    case '+':
        result = array[ADDITION];
        break;
    case '-':
        result = array[SUBTRACTION];
        break;
    case '*':
        result = array[MULTIPLICATION];
        break;
    case '/':
        result = array[DIVISION];
        break;
    case '(':
        result = array[LEFT_BRACKET];
        break;
    case ')':
        result = array[RIGHT_BRACKET];
        break;
    case '~':
        result = array[UNARY_MINUS];
        break;
    case '^':
        result = array[POWER];
        break;
    default:
        result = array[EMPTY];
        break;
    }

    return result;
}

std::string Operator::join()
{
    return std::string({ operators.at(ADDITION) })
        + std::string({ operators.at(SUBTRACTION) })
        + std::string({ operators.at(UNARY_MINUS) })
        + std::string({ operators.at(DIVISION) })
        + std::string({ operators.at(MULTIPLICATION) })
        + std::string({ operators.at(LEFT_BRACKET) })
        + std::string({ operators.at(RIGHT_BRACKET) })
        + std::string({ operators.at(POWER) })
        + std::string({ ' ' });
}
