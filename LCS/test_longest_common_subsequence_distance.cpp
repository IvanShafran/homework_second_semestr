#include "longest_common_subsequence.h"
#include "random_functions.h"

#include <vector>

int VagnerFisher(const std::vector<int>& first_vector, const std::vector<int>& second_vector)
{
    int first_size = first_vector.size();
    int second_size = second_vector.size();
    std::vector<int> previous_line;

    for (int i = 0; i <= first_size; i++) {
        std::vector<int> line;
        for (int j = 0; j <= second_size; j++)
        if (j == 0 || i == 0) {
            line.push_back(std::max(i, j));
        }
        else {
            if (first_vector[i - 1] == second_vector[j - 1])
                line.push_back(std::min(previous_line[j - 1],
                std::min(line[j - 1], previous_line[j]) + 1));
            else
                line.push_back(std::min(line[j - 1], previous_line[j]) + 1);
        }

        swap(previous_line, line);
    }

    return previous_line[second_size];
}

void TestLCSubsequenceDistance_Random()
{
    srand(777);
    for (int i = 0; i < 1000; i++)
    {
        int first_size = Rand(1, 1001);
        int second_size = Rand(1, 1001);
        std::vector<int>  element_set = { 1, 2, 3, 4, 5, 6, 7, 8 };
        std::vector<int> first_vector = RandVector(first_size, element_set);
        std::vector<int> second_vector = RandVector(second_size, element_set);

        if (LCSDistance(first_vector, second_vector) != VagnerFisher(first_vector, second_vector))
            throw std::runtime_error("Error: TestLCSubsequenceDistance_Random");

    }
}

void TestLCSubsequenceDistance()
{
    TestLCSubsequenceDistance_Random();
}
