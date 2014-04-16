#include <string>

#include "longest_common_subsequence.h"
#include "random_functions.h"

void TestFindLongestCommonSubsequence_Simple()
{
    if (FindLongestCommonSubsequence<std::string>("a", "b") != "")
        throw std::runtime_error("Error: TestLCSGetSubsequence_Simple #0");

    if (FindLongestCommonSubsequence<std::string>("a", "a") != "a")
        throw std::runtime_error("Error: TestLCSGetSubsequence_Simple #1");

    if (FindLongestCommonSubsequence<std::string>("ba", "aba") != "ba")
        throw std::runtime_error("Error: TestLCSGetSubsequence_Simple #2");

    if (FindLongestCommonSubsequence<std::string>("aba", "aba") != "aba")
        throw std::runtime_error("Error: TestLCSGetSubsequence_Simple #3");
    
    if (FindLongestCommonSubsequence<std::string>("abracadabra", "abacaba") != "abacaba")
        throw std::runtime_error("Error: TestLCSGetSubsequence_Simple #4");
    
    if (FindLongestCommonSubsequence<std::string>("avadakedavra", "abacaba") != "aaaa")
        throw std::runtime_error("Error: TestLCSGetSubsequence_Simple #5");

    if (FindLongestCommonSubsequence<std::string>("03.03.2014", "10:38") != "03")
        throw std::runtime_error("Error: TestLCSGetSubsequence_Simple #6");

    if (FindLongestCommonSubsequence<std::string>("abacaba", "ttatttbattttctttattbttatt")
        != "abacaba")
        throw std::runtime_error("Error: TestLCSGetSubsequence_Simple #7");
}

bool CheckSubsequence(std::string& string, std::string& substring)
{
    int position = 0;
    for (size_t i = 0; i < string.size(); i++)
    if (position != substring.size() && string[i] == substring[position])
        position++;

    if (position != substring.size())
        return false;
    else
        return true;
}

bool Check(std::string& first_string, std::string& second_string, std::string substring)
{
    int distance = LCSDistance(first_string, second_string);

    if (((first_string.size() + second_string.size() - distance) / 2) != substring.size())
        return false;

    if (!CheckSubsequence(first_string, substring) || !CheckSubsequence(second_string, substring))
        return false;

    return true;

}

void TestFindLongestCommonSubsequence_Random()
{
    srand(777);
    for (int count = 0; count < 100; count++) {
        int first_length = Rand(0, 1001);
        int second_length = Rand(0, 1001);
        std::string symbol_set = "abcdefghijklmnopqrstuvwxyz";
        std::string first_string = RandString(first_length, symbol_set);
        std::string second_string = RandString(second_length, symbol_set);
        std::string result = FindLongestCommonSubsequence<std::string>(first_string, 
            second_string);

        if (!Check(first_string, second_string, result))
            throw std::runtime_error("Error: TestLCSGetSubstring_Random");
    }
}

void TestFindLongestCommonSubsequence_BigTest()
{
    srand(777);
    for (int count = 0; count < 3; count++) {
        int first_length = 5000;
        int second_length = 5000;
        std::string symbol_set = 
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()-=";
        std::string first_string = RandString(first_length, symbol_set);
        std::string second_string = RandString(second_length, symbol_set);
        std::string result = FindLongestCommonSubsequence<std::string>(first_string, 
            second_string);

        if (!Check(first_string, second_string, result))
            throw std::runtime_error("Error: TestLCSGetSubstring_BigTest");
    }
}

void TestFindLongestCommonSubsequence()
{
    TestFindLongestCommonSubsequence_Simple();
    TestFindLongestCommonSubsequence_Random();
    TestFindLongestCommonSubsequence_BigTest();
}
