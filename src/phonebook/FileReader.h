#ifndef ALGORITHMS_FILEREADER_H
#define ALGORITHMS_FILEREADER_H

#include "Initable.h"
#include "Reader.h"
#include <string>
#include <vector>

using TFileLine = std::string;
using TFile = std::vector<TFileLine>;

class FileReader : public Reader<TFile>, public Initable<const std::string&, FileReader&> {
public:
    FileReader();

    explicit FileReader(const std::string& path);

    FileReader& init(const std::string& path) override;

    TFile get() override;

    void clear() override;
};

#endif //ALGORITHMS_FILEREADER_H
