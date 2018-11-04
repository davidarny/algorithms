#ifndef ALGORITHMS_CALCULATOR_H
#define ALGORITHMS_CALCULATOR_H

#include <string>

namespace Calculator {
static constexpr char EOLN = '\0';
static constexpr char SPACE = ' ';
static constexpr unsigned STRING_LENGTH = 256;

char* parse(char* pExpression);

bool isOperator(char op);

std::string trim(const std::string& str);

void toUniqueSpaces(char* pExpression);

void isValidChar(char ch);
}

#endif //ALGORITHMS_CALCULATOR_H
