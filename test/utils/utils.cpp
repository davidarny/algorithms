#include <fstream>

#include "utils.h"

void create_file(TString path)
{
    std::ofstream outfile(path);
    outfile << SAMPLE_TEXT << std::endl;
    outfile.close();
}
