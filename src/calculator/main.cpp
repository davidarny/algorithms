/*
4. В строке текстового файла задано выражение из целых
чисел и операций '+', '-', '*', '/', '^'. Порядок вычислений
определяется приоритетом операций и круглыми скобками. Возможен
одноместный минус в начале выражения или после открывающей
скобки. Преобразовать выражение в постфиксную форму (алгоритм
Дейкстры) и вычислить его значение. Показать этапы выполнения
(11)
Арутюнян Давид, ПС-23
gcc 7.2.0, CLion
*/

#ifdef _WIN32

#include <windows.h>

#endif

#include <iostream>
#include <string>

#include "calculator.h"

int main(int argc, char* argv[])
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    std::string line;
    std::getline(std::cin, line);
    line = Calculator::trim(line);
    try {
        auto postfix = Calculator::parse(line.data());
        auto result = Calculator::calculate(postfix);
        std::cout << result << std::endl;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}
