#ifndef ALGORITHMS_FILEADAPTER_H
#define ALGORITHMS_FILEADAPTER_H

#include "Adapter.h"
#include "FileReader.h"
#include "Initable.h"
#include <map>
#include <string>

using TMasterFileAdapterContent = std::map<int, std::string>;

class FileAdapter : public Adapter<TMasterFileAdapterContent>, public Initable<FileReader&, void> {
private:
    enum EFileCols {
        KEY = 0,
        VALUE
    };

    TMasterFileAdapterContent mContent;

    bool is_number(const std::string& s);

public:
    constexpr static char DELIMITER = ';';

    explicit FileAdapter(FileReader& reader);

    void init(FileReader& reader) override;

    std::map<int, std::string> convert() override;
};

#endif //ALGORITHMS_FILEADAPTER_H
