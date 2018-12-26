#ifndef ALGORITHMS_FILLSERVICE_H
#define ALGORITHMS_FILLSERVICE_H

#include "FileAdapter.h"
#include "Insertable.h"

class FillService {
public:
    template <typename T>
    static void fill(Insertable<T>& insertable, FileAdapter& adapter);
};

template <typename T>
void FillService::fill(Insertable<T>& insertable, FileAdapter& adapter)
{
    auto map = adapter.convert();
    for (const auto& row : map) {
        std::string copy(row.second);
        insertable.insert(row.first);
    }
}

#endif //ALGORITHMS_FILLSERVICE_H
