#ifndef ALGORITHMS_FILLSERVICE_H
#define ALGORITHMS_FILLSERVICE_H

#include "FileAdapter.h"
#include "Insertable.h"
#include "Table.h"

class FillService {
public:
    template <typename T>
    static void fill(Insertable<T>& insertable, FileAdapter& adapter);

    static void fill(Table& table, FileAdapter& adapter);
};

template <typename T>
void FillService::fill(Insertable<T>& insertable, FileAdapter& adapter)
{
    auto map = adapter.convert();
    for (const auto& row : map) {
        insertable.insert(row.first);
    }
}

void FillService::fill(Table& table, FileAdapter& adapter)
{
    auto map = adapter.convert();
    for (const auto& row : map) {
        table.row(row.first, row.second);
    }
}

#endif //ALGORITHMS_FILLSERVICE_H
