#ifndef ALGORITHMS_FILEADAPTER_H
#define ALGORITHMS_FILEADAPTER_H

#include "Adapter.h"
#include "FileReader.h"
#include "Initable.h"
#include <map>
#include <string>

using TFileAdapterContent = std::map<int, std::string>;

class FileAdapter : public Adapter<TFileAdapterContent>, public Initable<FileReader&, void> {
private:
    enum EFileCols {
        KEY = 0,
        VALUE
    };

    constexpr static char DELIMITER = ';';
    TFileAdapterContent mContent;

    bool is_number(const std::string& s);

public:
    explicit FileAdapter(FileReader& reader);

    void init(FileReader& reader) override;

    std::map<int, std::string> convert() override;
};

#endif //ALGORITHMS_FILEADAPTER_H
