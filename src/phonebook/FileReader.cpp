#include "FileReader.h"
#include <fstream>

TFile FileReader::get()
{
    return mContent;
}

FileReader::FileReader(const std::string& path)
{
    init(path);
}

FileReader& FileReader::init(const std::string& path)
{
    std::ifstream input;
    TFileLine line;
    input.open(path);
    if (!input) {
        throw std::runtime_error("Cannot read file \"" + path + "\"");
    }
    if (!input.is_open()) {
        throw std::runtime_error("Cannot open file \"" + path + "\"");
    }
    while (std::getline(input, line)) {
        mContent.emplace_back(line);
    }
    input.close();
    return *this;
}

void FileReader::clear()
{
    mContent.clear();
}

FileReader::FileReader() = default;
