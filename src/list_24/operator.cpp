#include "operator.h"

using namespace Operator;

void Operator::init(TOperator array[OPERATORS_SIZE])
{
    TOperator addition;
    addition.value = operators.at(ADDITION);
    addition.id = ADDITION;
    addition.priority = priorities.at(ADDITION);
    array[ADDITION] = addition;

    TOperator subtraction;
    subtraction.value = operators.at(SUBTRACTION);
    subtraction.id = SUBTRACTION;
    subtraction.priority = priorities.at(SUBTRACTION);
    array[SUBTRACTION] = subtraction;

    TOperator division;
    division.value = operators.at(DIVISION);
    division.id = DIVISION;
    division.priority = priorities.at(DIVISION);
    array[DIVISION] = division;

    TOperator multiplication;
    multiplication.value = operators.at(MULTIPLICATION);
    multiplication.id = MULTIPLICATION;
    multiplication.priority = priorities.at(MULTIPLICATION);
    array[MULTIPLICATION] = multiplication;

    TOperator left_bracket;
    left_bracket.value = operators.at(LEFT_BRACKET);
    left_bracket.id = LEFT_BRACKET;
    left_bracket.priority = priorities.at(LEFT_BRACKET);
    array[LEFT_BRACKET] = left_bracket;

    TOperator right_bracket;
    right_bracket.value = operators.at(RIGHT_BRACKET);
    right_bracket.id = RIGHT_BRACKET;
    right_bracket.priority = priorities.at(RIGHT_BRACKET);
    array[RIGHT_BRACKET] = right_bracket;

    TOperator empty;
    empty.value = operators.at(EMPTY);
    empty.id = EMPTY;
    empty.priority = priorities.at(EMPTY);
    array[EMPTY] = empty;
}

TOperator Operator::getByChar(char op)
{
    TOperator result;
    TOperator array[OPERATORS_SIZE];
    Operator::init(array);

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
    default:
        result = array[EMPTY];
        break;
    }

    return result;
}
