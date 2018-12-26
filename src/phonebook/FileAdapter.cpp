#include "FileAdapter.h"
#include <boost/algorithm/string.hpp>

std::map<int, std::string> FileAdapter::convert()
{
    return mContent;
}

void FileAdapter::init(FileReader& reader)
{
    auto map = reader.get();
    int index = 0;
    for (const auto& row : map) {
        std::vector<std::string> result;
        boost::split(result, row, [](char c) { return c == DELIMITER; });
        if (!is_number(result.at(EFileCols::KEY))) {
            throw std::runtime_error("Non-integer primary key found near line " + std::to_string(index));
        }
        try {
            auto key = std::stoi(result.at(EFileCols::KEY));
            auto value = result.at(EFileCols::VALUE);
            mContent[key] = value;
        } catch (std::exception& ex) {
            throw std::runtime_error("Error while paring table near line " + std::to_string(index));
        }
        index++;
    }
}

FileAdapter::FileAdapter(FileReader& reader)
{
    init(reader);
}

bool FileAdapter::is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}
