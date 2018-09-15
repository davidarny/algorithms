#include <boost/algorithm/string.hpp>

#include "Table.h"
#include "Converter.h"

TString Converter::convert(const TTable &table)
{
    for (const auto &row : table) {
        const auto group = row.at(header_index(EHeader::GROUP) + 1);
        const auto department = row.at(header_index(EHeader::DEPARTMENT) + 1);
        const bool isGroupFound = m_groups.count(group) != 0;
        TNumber score = static_cast<TNumber>(std::stoll(row.at(header_index(EHeader::AVERAGE_SCORE) + 1)));
        if (isGroupFound) {
            std::get<AVERAGE_SCORE>(m_groups.at(group)).push_back(score);
        } else {
            m_groups.insert({
                                group,
                                {department, group, {score}},
                            });
        }
    }
    for (const auto &m_group : m_groups) {
        auto& value = m_group.second;
        m_table.push_back({
            std::get<DEPARTMENT>(value),
            std::get<GROUP>(value),
            std::to_string(average_score_by_group(std::get<GROUP>(value))),
        });
    }
    return get();
}

TNumber Converter::average_score_by_group(TString group)
{
    auto& scores = std::get<AVERAGE_SCORE>(m_groups.at(group));
    TNumber average = 0;
    for (const auto &score : scores) {
        average += score;
    }
    return average / scores.size();
}

TNumber Converter::header_index(TString item)
{
    return static_cast<TNumber>(std::distance(
        m_header.begin(),
        std::find(m_header.begin(), m_header.end(), item))
    );
}

template<typename T, typename I>
TNumber Converter::index_of(T vector, I item)
{
    return static_cast<TNumber>(std::distance(
        vector.begin(),
        std::find(vector.begin(), vector.end(), item)
    ));
}

TString Converter::get()
{
    TString result;
    m_table.insert(m_table.begin(), m_header);
    for (const auto &row : m_table) {
        result += boost::join(row, Table::SPLIT_CHAR) + "\n";
    }
    result = result.substr(0, result.size() - 1);
    return result;
}

