#include "SlaveFileAdapter.h"
#include <boost/algorithm/string.hpp>

void SlaveFileAdapter::init(FileReader& reader)
{
    auto map = reader.get();
    int index = 0;
    for (const auto& row : map) {
        std::vector<std::string> result;
        boost::split(result, row, [](char c) { return c == DELIMITER; });
        try {
            auto key = result.at(EFileCols::KEY);
            auto value_1 = result.at(EFileCols::VALUE_1);
            auto value_2 = result.at(EFileCols::VALUE_2);
            std::vector<std::string> vector;
            vector.emplace_back(value_1);
            vector.emplace_back(value_2);
            mContent[key] = vector;
        } catch (std::exception& ex) {
            throw std::runtime_error("Error while paring table near line " + std::to_string(index));
        }
        index++;
    }
}

TSlaveFileAdapterContent SlaveFileAdapter::convert()
{
    return mContent;
}

SlaveFileAdapter::SlaveFileAdapter(FileReader& reader)
{
    init(reader);
}
