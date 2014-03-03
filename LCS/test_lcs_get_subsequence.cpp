#pragma once

#include <string>

#include "longest_common_subsequence.h"

void TestLCSGetSubsequence_Simple()
{/*
    if (LCSGetSubsequence<std::string>("a", "a") != "a")
        throw std::runtime_error("Error: TestLCSGetSubsequence_Simple #1");

    if (LCSGetSubsequence<std::string>("ba", "aba") != "ba")
        throw std::runtime_error("Error: TestLCSGetSubsequence_Simple #2");

    if (LCSGetSubsequence<std::string>("aba", "aba") != "aba")
        throw std::runtime_error("Error: TestLCSGetSubsequence_Simple #3");
    */
    if (LCSGetSubsequence<std::string>("abracadabra", "abacaba") != "abacaba")
        throw std::runtime_error("Error: TestLCSGetSubsequence_Simple #4");
}

void TestLCSGetSubsequence()
{
    TestLCSGetSubsequence_Simple();
}
