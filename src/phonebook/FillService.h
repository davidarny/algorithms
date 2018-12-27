#ifndef ALGORITHMS_FILLSERVICE_H
#define ALGORITHMS_FILLSERVICE_H

#include "Insertable.h"
#include "MasterFileAdapter.h"
#include "SlaveFileAdapter.h"
#include "Table.h"

class FillService {
public:
    template <typename T>
    static void fill(Insertable<T>& insertable, MasterFileAdapter& adapter);

    static void fill(Table& table, SlaveFileAdapter& adapter);
};

template <typename T>
void FillService::fill(Insertable<T>& insertable, MasterFileAdapter& adapter)
{
    auto map = adapter.convert();
    for (const auto& row : map) {
        insertable.insert(row.first, row.second);
    }
}

void FillService::fill(Table& table, SlaveFileAdapter& adapter)
{
    auto map = adapter.convert();
    for (const auto& row : map) {
        table.row(row.first, row.second);
    }
}

#endif //ALGORITHMS_FILLSERVICE_H
