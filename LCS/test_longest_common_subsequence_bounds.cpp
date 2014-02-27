#pragma once

#include <string>
#include <vector>

#include "random_functions.h"
#include "longest_common_subsequence.h"

std::vector<size_t> VagnerFisherBounds(const std::string& first_vector, const std::string& second_vector,
    int distance)
{
    int first_size = first_vector.size();
    int second_size = second_vector.size();
    std::vector<int> previous_line;
    std::vector<size_t> bounds;
    bounds.resize(2 * distance + 1);
    int shift = distance;

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
            if (line.back() == distance)
                bounds[j - i] = i;
        }

        swap(previous_line, line);
    }

    return bounds;
}

void TestLCSBounds_Random()
{
    for (int i = 0; i < 1000; i++)
    {
        int first_length = Rand(1, 1001);
        int second_length = Rand(1, 1001);
        std::string  symbol_set = "abcdefgh";
        std::string first_string = RandString(first_length, symbol_set);
        std::string second_string = RandString(second_length, symbol_set);
        size_t distance = Rand(0, LCSDistance(first_string, second_string) + 1);

        std::vector<size_t> true_bounds = VagnerFisherBounds(first_string, second_string, distance);
        std::vector<size_t> bounds = LCSBounds(first_string.begin(), first_string.end(),
            second_string.begin(), second_string.end(), distance);
        !!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (0 != memcmp(&true_bounds[-first_length + distance], &bounds[-first_length + distance], 
            (first_length + second_length) * sizeof(size_t)))
            throw std::runtime_error("Error: TestLCSubstring_Random");
    }
}

void TestLCSBounds()
{
    TestLCSBounds_Random();
}