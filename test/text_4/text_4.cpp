#include <string_view>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>

#include "doctest.h"
#include "text_4/text_4.h"
#include "../utils/utils.h"

static TString PATH = "text_4.txt";


TEST_CASE ("text_4 creates file")
{
    create_file(PATH);
    std::ifstream input;
    input.open(PATH);
        CHECK(input);
    std::remove(PATH.data());
}

TEST_CASE ("text_4 reads file")
{
    create_file(PATH);
    TString result = text_4(PATH);
        CHECK(result.size() != 0);
    std::remove(PATH.data());
}
