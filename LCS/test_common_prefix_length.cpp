#pragma once

#include "random_functions.h"
#include "longest_common_subsequence.h"

void TestCPL_Simple()
{
    std::string first_string;
    std::string second_string;

    first_string = "";
    second_string = "";
    if (CommonPrefixLength(first_string.begin(), first_string.end(),
        second_string.begin(), second_string.end()) != 0)
        throw std::runtime_error("Error on TestCommonPrefixLength_Simple #1");

    first_string = "a";
    second_string = "b";
    if (CommonPrefixLength(first_string.begin(), first_string.end(),
        second_string.begin(), second_string.end()) != 0)
        throw std::runtime_error("Error on TestCommonPrefixLength_Simple #2");

    first_string = "abacaba";
    second_string = "aba";
    if (CommonPrefixLength(first_string.begin(), first_string.end(),
        second_string.begin(), second_string.end()) != 3)
        throw std::runtime_error("Error on TestCommonPrefixLength_Simple #3");

    first_string = "abacaba";
    second_string = "bacb";
    if (CommonPrefixLength(first_string.begin() + 1, first_string.end(),
        second_string.begin(), second_string.end()) != 3)
        throw std::runtime_error("Error on TestCommonPrefixLength_Simple #4");

    first_string = "abacaba";
    second_string = "abacaba";
    if (CommonPrefixLength(first_string.begin(), first_string.end(),
        second_string.begin(), second_string.end()) != 7)
        throw std::runtime_error("Error on TestCommonPrefixLength_Simple #5");

}

bool Check(size_t first_position, size_t second_position,
    const std::string& first_string, const std::string& second_string,
    int common_prefix_length)
{
    if (common_prefix_length < 0 || (first_position + common_prefix_length) > first_string.length()
        || (second_position + common_prefix_length) > second_string.length())
        return false;

    if (0 != memcmp(&first_string[first_position],
                    &second_string[second_position],
                    common_prefix_length * sizeof(first_string[first_position]))) {
        return false;
    }

    if ((first_position + common_prefix_length) < first_string.length()
        && (second_position + common_prefix_length) < second_string.length()
        && (first_string[first_position + common_prefix_length] == second_string[second_position + common_prefix_length]))
        return false;

    return true;
}

void TestCPL_Random()
{
    srand(777);

    std::string first_string, second_string;
    for (int i = 0; i < 1000; i++)
    {
        int first_length = Rand(1, 1001);
        int second_length = Rand(1, 1001);
        std::string symbol_set = "ab";
        first_string = RandString(first_length, symbol_set);
        second_string = RandString(second_length, symbol_set);

        size_t first_position = Rand(0, first_length);
        size_t second_position = Rand(0, second_length);
        int common_prefix_length = CommonPrefixLength(first_string.begin() + first_position, 
            first_string.end(), second_string.begin() + second_position, second_string.end());

        if (!Check(first_position, second_position,
            first_string, second_string, common_prefix_length))
            throw std::runtime_error("Error on TestCommonStringLength_Random");
    }
}

void TestCommonPrefixLength()
{
    TestCPL_Simple();
    TestCPL_Random();
}
