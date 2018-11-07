#ifndef ALGORITHMS_CALCULATOR_H
#define ALGORITHMS_CALCULATOR_H

#include <string>

namespace Calculator {
static constexpr char EOLN = '\0';
static constexpr char SPACE = ' ';
static constexpr unsigned STRING_LENGTH = 256;

char* parse(char* expression);

bool isOperator(char op);

std::string trim(const std::string& str);

void trimAll(char* expression);
}

#endif //ALGORITHMS_CALCULATOR_H
