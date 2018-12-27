#ifndef ALGORITHMS_TABLE_H
#define ALGORITHMS_TABLE_H

#include <any>
#include <map>
#include <string>
#include <vector>

using TRow = std::vector<std::pair<std::string, std::string>>;

class Table {
private:
    std::vector<std::string> mCols;
    std::map<std::string, TRow> mRows;

public:
    Table& column(const std::string& column);

    Table& row(const std::string& id, const std::vector<std::string>& row);
};

#endif //ALGORITHMS_TABLE_H
