#include <iostream>
#include "text_4.h"

int main(int argc, char *argv[])
{
    TString path = argv[1];
    TString text;
    try {
        text = text_4(path);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    std::cout << text << std::endl;
}
