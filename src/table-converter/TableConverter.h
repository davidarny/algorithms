#ifndef ALGORITHMS_OUTPUTTABLE_H
#define ALGORITHMS_OUTPUTTABLE_H

#include <map>
#include <tuple>

#include "EHeader.h"
#include "Table.h"

using TNumber = unsigned long long;
using TSignedNumber = long long;
using TScores = std::vector<TNumber>;
using TGroups = std::map<TString, std::tuple<TString, TString, TScores>>;

class TableConverter {
private:
    enum EConverterOrder {
        DEPARTMENT = 0,
        GROUP,
        AVERAGE_SCORE
    };

    TTable mTable{};
    TGroups mGroups{};
    THeader mHeader{
        EHeader::DEPARTMENT,
        EHeader::GROUP,
        EHeader::AVERAGE_SCORE,
    };

    TNumber averageScoreByGroup(TString group);

    TNumber headerIndex(TString item);

    TString get();

    template <typename T, typename I>
    TNumber indexOf(T vector, I item);

public:
    TString convert(const TTable& table);
};

#endif //ALGORITHMS_OUTPUTTABLE_H
