#include "longest_common_subsequence.h"
#include "random_functions.h"
#include "vagner_fisher.h"

#include <vector>

void TestLCSubsequenceDistance_Random()
{
    srand(777);
    for (int i = 0; i < 100; i++)
    {
        int first_size = Rand(1, 1001);
        int second_size = Rand(1, 1001);
        std::vector<int>  element_set = { 1, 2, 3, 4, 5, 6, 7, 8 };
        std::vector<int> first_vector = RandVector(first_size, element_set);
        std::vector<int> second_vector = RandVector(second_size, element_set);

        if (LCSDistance(first_vector, second_vector) != 
            GetCLongestCommonSubsequenceByVagnerFisherAlgo(first_vector, second_vector))
            throw std::runtime_error("Error: TestLCSubsequenceDistance_Random");

    }
}

void TestLCSubsequenceDistance()
{
    TestLCSubsequenceDistance_Random();
}
