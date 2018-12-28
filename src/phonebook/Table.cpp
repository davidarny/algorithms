#include "Table.h"
#include "FileAdapter.h"
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

Table& Table::setValueById(int id, std::string value, const std::string& path)
{
    for (auto& item : mRows) {
        if (item.first == id) {
            item.second = value;
            break;
        }
    }
    sync(path);
    return *this;
}

void Table::sync(const std::string& path)
{
    std::ofstream ofs;
    ofs.open(path, std::ofstream::out | std::ofstream::trunc);
    for (const auto& item : mRows) {
        ofs << item.first << FileAdapter::DELIMITER << item.second << std::endl;
    }
    ofs.close();
}

int Table::getMaxId()
{
    int result = 0;
    for (const auto& item : mRows) {
        if (item.first > result) {
            result = item.first;
        }
    }
    return result;
}

Table& Table::deleteValueById(int id)
{
    mRows.erase(id);
    return *this;
}
