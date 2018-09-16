#include <utility>

#ifndef ALGORITHMS_INPUTTABLE_H
#define ALGORITHMS_INPUTTABLE_H

#include "EHeader.h"
#include "TableConverter.h"

class InputTable
{
private:
    THeader header{
        EHeader::LAST_NAME,
        EHeader::DEPARTMENT,
        EHeader::GROUP,
        EHeader::AVERAGE_SCORE,
    };
    Table table;

public:
    InputTable(std::vector<TString> &rows);

    const TTable &getTable() const;
};


#endif //ALGORITHMS_INPUTTABLE_H
