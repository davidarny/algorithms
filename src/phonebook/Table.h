#ifndef ALGORITHMS_TABLE_H
#define ALGORITHMS_TABLE_H

#include <any>
#include <map>
#include <string>
#include <vector>

class Table {
private:
    std::map<int, std::string> mRows;

    void sync();

public:
    Table& row(int id, const std::string& row);

    int getIdByValue(const std::string& value);

    std::string getValueById(int id);

    Table& setValueById(int id, std::string value);
};

#endif //ALGORITHMS_TABLE_H
