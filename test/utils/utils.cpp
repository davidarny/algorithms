#include <fstream>

#include "utils.h"

void createFile(TString path, TString sample)
{
    std::ofstream outfile(path);
    outfile << sample << std::endl;
    outfile.close();
}
