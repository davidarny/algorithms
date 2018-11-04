/*
 20. Имеется  некоторое  алгебраическое выражение.  Операнды
заданы идентификаторами,  операции выполняются по приоритетам,
допускается использование круглых скобок. Возможны одноместные
операции '+' и '-', а также операция возведения в степень '^'.
Требуется построить и выдать в наглядном виде бинарное дерево,
представляющее данное выражение (12).
Арутюнян Давид, ПС-23
gcc 8.1.0, CLion
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
        std::cout << postfix << std::endl;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}
