#ifndef ALGORITHMS_SLAVEFILEADAPTER_H
#define ALGORITHMS_SLAVEFILEADAPTER_H

#include "Adapter.h"
#include "FileReader.h"
#include "Initable.h"
#include <map>
#include <string>

using TSlaveFileAdapterContent = std::map<std::string, std::vector<std::string>>;

class SlaveFileAdapter : public Adapter<TSlaveFileAdapterContent>, public Initable<FileReader&, void> {
private:
    enum EFileCols {
        KEY = 0,
        VALUE_1,
        VALUE_2,
    };

    constexpr static char DELIMITER = ';';
    TSlaveFileAdapterContent mContent;

public:
    explicit SlaveFileAdapter(FileReader& reader);

    TSlaveFileAdapterContent convert() override;

public:
    void init(FileReader& reader) override;
};

#endif //ALGORITHMS_SLAVEFILEADAPTER_H
