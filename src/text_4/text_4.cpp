#include <fstream>
#include <vector>

#include "text_4.h"
#include "Table.h"
#include "InputTable.h"

TString text_4(TString path)
{
    TRow lines;
    TString line;
    std::ifstream input(path, std::ios::binary);
    if (!input) {
        throw std::runtime_error("Unable to open file in path " + path);
    }
    while (std::getline(input, line)) {
        lines.push_back(line);
        line.clear();
    }
    InputTable inputTable{lines};
    Converter converter{};
    return converter.convert(inputTable.getTable());
}
