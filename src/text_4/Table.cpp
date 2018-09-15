#include <boost/algorithm/string.hpp>
#include <boost/range/adaptors.hpp>

#include "Table.h"
#include "Converter.h"

void Table::parse(TLines lines)
{
    TNumber index = 0;
    for (const auto &line : lines) {
        TRow row;
        boost::split(row, line, boost::is_any_of(Table::SPLIT_CHAR));
        const bool isRowValid = std::any_of(row.begin(), row.end(), [&](auto value) {
            return std::find(header.begin(), header.end(), value) != header.end();
        });
        if (isRowValid) {
            continue;
        }
        if (row.size() != header.size()) {
            throw std::length_error("Error while parsing data at line " + std::to_string(index + 1));
        }
        table.push_back(std::move(row));
        index++;
    }
}

Table::Table(
    THeader header,
    TLines lines
)
    : header(std::move(header))
{
    table = {};
    parse(std::move(lines));
}

const TTable &Table::getTable() const
{
    return table;
}

