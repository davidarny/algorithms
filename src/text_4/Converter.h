#ifndef ALGORITHMS_OUTPUTTABLE_H
#define ALGORITHMS_OUTPUTTABLE_H

#include <tuple>
#include <map>

#include "EHeader.h"
#include "Table.h"

using TNumber = unsigned long long;
using TScores = std::vector<TNumber>;
using TGroups = std::map<TString, std::tuple<TString, TString, TScores>>;

class Converter
{
private:
    enum EConverterOrder {
        DEPARTMENT = 0,
        GROUP,
        AVERAGE_SCORE
    };

    TTable m_table{};
    TGroups m_groups{};
    THeader m_header{
        EHeader::DEPARTMENT,
        EHeader::GROUP,
        EHeader::AVERAGE_SCORE,
    };

    TNumber average_score_by_group(TString group);

    TNumber header_index(TString item);

    TString get();

    template<typename T, typename I>
    TNumber index_of(T vector, I item);

public:
    TString convert(const TTable &table);
};

#endif //ALGORITHMS_OUTPUTTABLE_H
