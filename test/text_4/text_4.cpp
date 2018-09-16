#include <string_view>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>

#include "doctest.h"
#include "text_4/text_4.h"
#include "../utils/utils.h"

static const TString SAMPLE_TEXT = "Second name Department Group Average score\n"
                                   "Arutiunian FIiVT PS-23 100\n"
                                   "Scheglova FIiVT PS-23 50";
static const TString PATH = "text_4.txt";

TEST_CASE ("text_4 creates file")
{
    create_file(PATH, SAMPLE_TEXT);
    std::ifstream input;
    input.open(PATH);
        CHECK(input);
    std::remove(PATH.data());
}

TEST_CASE ("text_4 reads file")
{
    create_file(PATH, SAMPLE_TEXT);
    TString result = text_4(PATH);
        CHECK(result.size() != 0);
    std::remove(PATH.data());
}
