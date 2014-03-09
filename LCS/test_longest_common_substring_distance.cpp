#include "longest_common_subsequence.h"
#include "random_functions.h"

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

int VagnerFisher(const std::string& first_string, const std::string& second_string)
{
    int first_length = first_string.length();
    int second_length = second_string.length();
    std::vector<int> previous_line;

    for (int i = 0; i <= first_length; i++) {
        std::vector<int> line;
        for (int j = 0; j <= second_length; j++)
        if (j == 0 || i == 0) {
            line.push_back(std::max(i, j));
        }
        else {
            if (first_string[i - 1] == second_string[j - 1])
                line.push_back(std::min(previous_line[j - 1],
                std::min(line[j - 1], previous_line[j]) + 1));
            else
                line.push_back(std::min(line[j - 1], previous_line[j]) + 1);
        }

        swap(previous_line, line);
    }

    return previous_line[second_length];
}

void TestLCSubstringDistance_Random()
{
    srand(777);
    for (int i = 0; i < 1000; i++)
    {
        int first_length = Rand(1, 1001);
        int second_length = Rand(1, 1001);
        std::string  symbol_set = "abcdefgh";
        std::string first_string = RandString(first_length, symbol_set);
        std::string second_string = RandString(second_length, symbol_set);
        int result = LCSDistance(first_string, second_string);
        int answer = VagnerFisher(first_string, second_string);

        if (result != answer)
            throw std::runtime_error("Error: TestLCSubstringDistance_Random");

    }
}

void TestLCSubstringDistance()
{
    TestLCSubstringDistance_Simple();
    TestLCSubstringDistance_Random();
}
