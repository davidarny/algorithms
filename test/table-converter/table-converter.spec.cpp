#include <boost/algorithm/string.hpp>
#include <fstream>
#include <string>
#include <string_view>

#include "../utils/utils.h"
#include "doctest.h"
#include "table-converter/table-converter.h"

static const TString SAMPLE_TEXT = "Second name Department Group Average score\n"
                                   "Arutiunian FIiVT PS-23 100\n"
                                   "Scheglova FIiVT PS-23 50";
static const TString PATH = "table-converter.mock.txt";

TEST_CASE("table-converter creates file")
{
    create_file(PATH, SAMPLE_TEXT);
    std::ifstream input;
    input.open(PATH);
    CHECK(input);
    std::remove(PATH.data());
}

TEST_CASE("table-converter reads file")
{
    create_file(PATH, SAMPLE_TEXT);
    TString result = table_converter(PATH);
    CHECK(result.size() != 0);
    std::remove(PATH.data());
}
