#include <fstream>
#include <vector>

#include "InputTable.h"
#include "Table.h"
#include "table-converter.h"

TString table_converter(TString path)
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
    InputTable inputTable{ lines };
    TableConverter tableConverter{};
    return tableConverter.convert(inputTable.getTable());
}
