#include <algorithm>
#include <boost/algorithm/string.hpp>

#include "Table.h"
#include "TableConverter.h"

TString TableConverter::convert(const TTable& table)
{
    for (const auto& row : table) {
        const auto group = row.at(headerIndex(EHeader::GROUP) + 1);
        const auto department = row.at(headerIndex(EHeader::DEPARTMENT) + 1);
        const bool isGroupFound = mGroups.count(group) != 0;
        TNumber score = static_cast<TNumber>(std::stoll(row.at(headerIndex(EHeader::AVERAGE_SCORE) + 1)));
        if (isGroupFound) {
            std::get<AVERAGE_SCORE>(mGroups.at(group)).push_back(score);
        } else {
            mGroups.insert({
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
    for (const auto& mGroup : mGroups) {
        auto& value = mGroup.second;
        auto score = static_cast<TSignedNumber>(averageScoreByGroup(std::get<GROUP>(value)));
        if (score >= maxAverageScore) {
            maxAverageScore = score;
            std::vector<std::pair<TNumber, TSignedNumber>> buffer{};
            std::copy_if(
                maxAverageScoreIndexes.begin(),
                maxAverageScoreIndexes.end(),
                std::back_inserter(buffer),
                [&](std::pair<TNumber, TNumber> value) { return value.second == score; });
            maxAverageScoreIndexes = buffer;
            maxAverageScoreIndexes.emplace_back(index, score);
        }
        if (score <= minAverageScore) {
            minAverageScore = score;
            std::vector<std::pair<TNumber, TSignedNumber>> buffer{};
            std::copy_if(
                minAverageScoreIndexes.begin(),
                minAverageScoreIndexes.end(),
                std::back_inserter(buffer),
                [&](std::pair<TNumber, TNumber> value) { return value.second == score; });
            minAverageScoreIndexes.emplace_back(index, score);
        }
        mTable.push_back({
            std::get<DEPARTMENT>(value),
            std::get<GROUP>(value),
            std::to_string(score),
        });
        index++;
    }
    for (const auto& maxAverageScoreIndex : maxAverageScoreIndexes) {
        mTable.at(maxAverageScoreIndex.first).at(AVERAGE_SCORE).append("\u0020↑↑↑");
    }
    for (const auto& minAverageScoreIndex : minAverageScoreIndexes) {
        mTable.at(minAverageScoreIndex.first).at(AVERAGE_SCORE).append("\u0020↓↓↓");
    }
    return get();
}

TNumber TableConverter::averageScoreByGroup(TString group)
{
    auto& scores = std::get<AVERAGE_SCORE>(mGroups.at(group));
    TNumber average = 0;
    for (const auto& score : scores) {
        average += score;
    }
    return average / scores.size();
}

TNumber TableConverter::headerIndex(TString item)
{
    return static_cast<TNumber>(std::distance(
        mHeader.begin(),
        std::find(mHeader.begin(), mHeader.end(), item)));
}

template <typename T, typename I>
TNumber TableConverter::indexOf(T vector, I item)
{
    return static_cast<TNumber>(std::distance(
        vector.begin(),
        std::find(vector.begin(), vector.end(), item)));
}

TString TableConverter::get()
{
    TString result;
    mTable.insert(mTable.begin(), mHeader);
    for (const auto& row : mTable) {
        result += boost::join(row, Table::SPLIT_CHAR) + "\n";
    }
    result = result.substr(0, result.size() - 1);
    return result;
}
