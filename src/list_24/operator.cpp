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

    TOperator left_bracket;
    left_bracket.value = operators.at(LEFT_BRACKET);
    left_bracket.id = LEFT_BRACKET;
    left_bracket.priority = priorities.at(LEFT_BRACKET);
    left_bracket.associativity = LEFT;
    array[LEFT_BRACKET] = left_bracket;

    TOperator right_bracket;
    right_bracket.value = operators.at(RIGHT_BRACKET);
    right_bracket.id = RIGHT_BRACKET;
    right_bracket.priority = priorities.at(RIGHT_BRACKET);
    right_bracket.associativity = LEFT;
    array[RIGHT_BRACKET] = right_bracket;

    TOperator unary_minus;
    unary_minus.value = operators.at(UNARY_MINUS);
    unary_minus.id = UNARY_MINUS;
    unary_minus.priority = priorities.at(UNARY_MINUS);
    unary_minus.associativity = LEFT;
    array[UNARY_MINUS] = unary_minus;

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
