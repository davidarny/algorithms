#include <algorithm>
#include <boost/algorithm/string.hpp>

#include "Table.h"
#include "TableConverter.h"

TString TableConverter::convert(const TTable& table)
{
    for (const auto& row : table) {
        const auto group = row.at(header_index(EHeader::GROUP) + 1);
        const auto department = row.at(header_index(EHeader::DEPARTMENT) + 1);
        const bool isGroupFound = m_groups.count(group) != 0;
        TNumber score = static_cast<TNumber>(std::stoll(row.at(header_index(EHeader::AVERAGE_SCORE) + 1)));
        if (isGroupFound) {
            std::get<AVERAGE_SCORE>(m_groups.at(group)).push_back(score);
        } else {
            m_groups.insert({
                group,
                { department, group, { score } },
            });
        }
    }
    TSignedNumber minAverageScore = LONG_LONG_MAX;
    TSignedNumber maxAverageScore = LONG_LONG_MIN;
    // Pair<index, averageScoreByGroup>
    std::vector<std::pair<TNumber, TSignedNumber>> maxAverageScoreIndexes{};
    // Pair<index, averageScoreByGroup>
    std::vector<std::pair<TNumber, TSignedNumber>> minAverageScoreIndexes{};
    TNumber index = 0;
    for (const auto& m_group : m_groups) {
        auto& value = m_group.second;
        auto averageScoreByGroup = static_cast<TSignedNumber>(average_score_by_group(std::get<GROUP>(value)));
        if (averageScoreByGroup >= maxAverageScore) {
            maxAverageScore = averageScoreByGroup;
            std::vector<std::pair<TNumber, TSignedNumber>> buffer{};
            std::copy_if(
                maxAverageScoreIndexes.begin(),
                maxAverageScoreIndexes.end(),
                std::back_inserter(buffer),
                [&](std::pair<TNumber, TNumber> value) { return value.second == averageScoreByGroup; });
            maxAverageScoreIndexes = buffer;
            maxAverageScoreIndexes.emplace_back(index, averageScoreByGroup);
        }
        if (averageScoreByGroup <= minAverageScore) {
            minAverageScore = averageScoreByGroup;
            std::vector<std::pair<TNumber, TSignedNumber>> buffer{};
            std::copy_if(
                minAverageScoreIndexes.begin(),
                minAverageScoreIndexes.end(),
                std::back_inserter(buffer),
                [&](std::pair<TNumber, TNumber> value) { return value.second == averageScoreByGroup; });
            minAverageScoreIndexes.emplace_back(index, averageScoreByGroup);
        }
        m_table.push_back({
            std::get<DEPARTMENT>(value),
            std::get<GROUP>(value),
            std::to_string(averageScoreByGroup),
        });
        index++;
    }
    for (const auto& maxAverageScoreIndex : maxAverageScoreIndexes) {
        m_table.at(maxAverageScoreIndex.first).at(AVERAGE_SCORE).append("\u0020↑↑↑");
    }
    for (const auto& minAverageScoreIndex : minAverageScoreIndexes) {
        m_table.at(minAverageScoreIndex.first).at(AVERAGE_SCORE).append("\u0020↓↓↓");
    }
    return get();
}

TNumber TableConverter::average_score_by_group(TString group)
{
    auto& scores = std::get<AVERAGE_SCORE>(m_groups.at(group));
    TNumber average = 0;
    for (const auto& score : scores) {
        average += score;
    }
    return average / scores.size();
}

TNumber TableConverter::header_index(TString item)
{
    return static_cast<TNumber>(std::distance(
        m_header.begin(),
        std::find(m_header.begin(), m_header.end(), item)));
}

template <typename T, typename I>
TNumber TableConverter::index_of(T vector, I item)
{
    return static_cast<TNumber>(std::distance(
        vector.begin(),
        std::find(vector.begin(), vector.end(), item)));
}

TString TableConverter::get()
{
    TString result;
    m_table.insert(m_table.begin(), m_header);
    for (const auto& row : m_table) {
        result += boost::join(row, Table::SPLIT_CHAR) + "\n";
    }
    result = result.substr(0, result.size() - 1);
    return result;
}
