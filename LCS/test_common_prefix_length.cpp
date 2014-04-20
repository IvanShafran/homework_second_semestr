#include <cstring>
#include <string>
#include <algorithm>

#include "random_functions.h"
#include "longest_common_subsequence.h"

int GetCPL(std::string first_string, std::string second_string)
{
    return CommonPrefixLength(first_string.begin(), first_string.end(),
        second_string.begin(), second_string.end());
}

void TestCommonPrefixLength_Simple()
{
    if (GetCPL("", "") != 0)
        throw std::runtime_error("Error on TestCommonPrefixLength_Simple #1");

    if (GetCPL("a", "b") != 0)
        throw std::runtime_error("Error on TestCommonPrefixLength_Simple #2");

    if (GetCPL("abacaba", "aba") != 3)
        throw std::runtime_error("Error on TestCommonPrefixLength_Simple #3");

    if (GetCPL("bacaba", "bacb") != 3)
        throw std::runtime_error("Error on TestCommonPrefixLength_Simple #4");

    if (GetCPL("abacaba", "abacaba") != 7)
        throw std::runtime_error("Error on TestCommonPrefixLength_Simple #5");

}

bool CheckCommonPrefixLength(const std::string& first_string,
    const std::string& second_string, 
    int common_prefix_length)
{
    // @review: Хорошо бы проверить, что common_prefix_length не входит за границы строк.
    return !std::equal(first_string.begin(), first_string.begin() + common_prefix_length, second_string.begin()) ||
        ((first_string.size() != common_prefix_length) &&
         (second_string.size() != common_prefix_length) &&
         (first_string[common_prefix_length] == second_string[common_prefix_length]));
}

void TestCommonPrefixLength_Random()
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

        int common_prefix_length = CommonPrefixLength(first_string.begin(), 
            first_string.end(), second_string.begin(), second_string.end());

        if (CheckCommonPrefixLength(first_string, second_string, 
            common_prefix_length))
            throw std::runtime_error("Error on TestCommonStringLength_Random");
    }
}

void TestCommonPrefixLength()
{
    TestCommonPrefixLength_Simple();
    TestCommonPrefixLength_Random();
}
