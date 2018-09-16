#include <fstream>

#include "utils.h"

void create_file(TString path, TString sample)
{
    std::ofstream outfile(path);
    outfile << sample << std::endl;
    outfile.close();
}
