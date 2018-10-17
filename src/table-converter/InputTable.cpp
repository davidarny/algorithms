#include <boost/algorithm/string.hpp>

#include "InputTable.h"

InputTable::InputTable(std::vector<TString>& rows)
    : table(header, rows)
{
}

const TTable& InputTable::getTable() const
{
    return table.getTable();
}
