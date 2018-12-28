#include "Table.h"
#include "FileAdapter.h"
#include "FileRepository.h"
#include <algorithm>
#include <fstream>
#include <limits>

Table& Table::row(int id, const std::string& row)
{
    mRows[id] = row;
    return *this;
}

int Table::getIdByValue(const std::string& value)
{
    int result = std::numeric_limits<int>::max();
    for (const auto& item : mRows) {
        auto id = item.first;
        auto data = item.second;
        if (data == value) {
            result = id;
            break;
        }
    }
    return result;
}

std::string Table::getValueById(int id)
{
    std::string result;
    for (const auto& item : mRows) {
        if (item.first == id) {
            result = item.second;
            break;
        }
    }
    return result;
}

Table& Table::setValueById(int id, std::string value)
{
    for (auto& item : mRows) {
        if (item.first == id) {
            item.second = value;
            break;
        }
    }
    sync();
    return *this;
}

void Table::sync()
{
    std::ofstream ofs;
    ofs.open(FileRepository::getSlaveFilePath(), std::ofstream::out | std::ofstream::trunc);
    for (const auto& item : mRows) {
        ofs << item.first << FileAdapter::DELIMITER << item.second << std::endl;
    }
    ofs.close();
}
