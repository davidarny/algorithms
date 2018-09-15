#ifndef ALGORITHMS_TABLE_H
#define ALGORITHMS_TABLE_H

#include <string_view>
#include <map>
#include <vector>
#include <algorithm>

#include "text_4.h"

using TLines = std::vector<TString>;
using THeader = std::vector<TString>;
using TRow = std::vector<TString>;
using TTable = std::vector<TRow>;

class Table
{
private:
    THeader header;
    TTable table;

    void parse(TLines lines);

public:
    const TTable &getTable() const;

    static constexpr char SPLIT_CHAR[2]{" "};

    Table(THeader header,
          TLines lines);
};


#endif //ALGORITHMS_TABLE_H
