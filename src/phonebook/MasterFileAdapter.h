#ifndef ALGORITHMS_MASTERFILEADAPTER_H
#define ALGORITHMS_MASTERFILEADAPTER_H

#include "Adapter.h"
#include "FileReader.h"
#include "Initable.h"
#include <map>
#include <string>

using TMasterFileAdapterContent = std::map<int, std::string>;

class MasterFileAdapter : public Adapter<TMasterFileAdapterContent>, public Initable<FileReader&, void> {
private:
    enum EFileCols {
        KEY = 0,
        VALUE
    };

    constexpr static char DELIMITER = ';';
    TMasterFileAdapterContent mContent;

    bool is_number(const std::string& s);

public:
    explicit MasterFileAdapter(FileReader& reader);

    void init(FileReader& reader) override;

    std::map<int, std::string> convert() override;
};

#endif //ALGORITHMS_MASTERFILEADAPTER_H
