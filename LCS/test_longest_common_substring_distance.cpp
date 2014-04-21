#include "longest_common_subsequence.h"
#include "random_functions.h"
#include "vagner_fisher.h"

#include <vector>

void TestLCSubstringDistance_Simple()
{
    if (LCSDistance<std::string>("", "") != 0)
        throw std::runtime_error("Error: TestLCSubstringDistance_Simple #1");

    if (LCSDistance<std::string>("", "a") != 1)
        throw std::runtime_error("Error: TestLCSubstringDistance_Simple #2");

    if (LCSDistance<std::string>("a", "") != 1)
        throw std::runtime_error("Error: TestLCSubstringDistance_Simple #3");

    if (LCSDistance<std::string>("a", "b") != 2)
        throw std::runtime_error("Error: TestLCSubstringDistance_Simple #4");

    if (LCSDistance<std::string>("a", "a") != 0)
        throw std::runtime_error("Error: TestLCSubstringDistance_Simple #5");

    if (LCSDistance<std::string>("abacaba", "bab") != 4)
        throw std::runtime_error("Error: TestLCSubstringDistance_Simple #6");

    if (LCSDistance<std::string>("abacaba", "acab") != 3)
        throw std::runtime_error("Error: TestLCSubstringDistance_Simple #7");

    if (LCSDistance<std::string>("abbaba", "babba") != 3)
        throw std::runtime_error("Error: TestLCSubstringDistance_Simple #8");

    if (LCSDistance<std::string>("bababa", "aba") != 3)
        throw std::runtime_error("Error: TestLCSubstringDistance_Simple #9");
}

void TestLCSubstringDistance_Random()
{
    srand(777);
    for (int i = 0; i < 100; i++)
    {
        int first_length = Rand(1, 1001);
        int second_length = Rand(1, 1001);
        std::string  symbol_set = "abcdefgh";
        std::string first_string = RandString(first_length, symbol_set);
        std::string second_string = RandString(second_length, symbol_set);
        int result = LCSDistance(first_string, second_string);
        int answer = 
            GetCLongestCommonSubsequenceByVagnerFisherAlgo(first_string, second_string);

        if (result != answer)
            throw std::runtime_error("Error: TestLCSubstringDistance_Random");

    }
}

void TestLCSubstringDistance()
{
    TestLCSubstringDistance_Simple();
    TestLCSubstringDistance_Random();
}
