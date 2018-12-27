#include "Table.h"

Table& Table::column(const std::string& column)
{
    std::string copy(column);
    mCols.emplace_back(copy);
    return *this;
}

Table& Table::row(const std::string& id, const std::vector<std::string>& row)
{
    int index = 0;
    std::vector<std::pair<std::string, std::string>> vector;
    for (const auto& col : mCols) {
        if (index > row.size() - 1) {
            continue;
        }
        auto pair = std::pair(col, row.at(static_cast<unsigned long>(index)));
        vector.emplace_back(pair);
        index++;
    }
    mRows[id] = vector;
    return *this;
}
