#pragma once

template <class Sequence>
int GetCLongestCommonSubsequenceByVagnerFisherAlgo(const Sequence& first_vector, 
    const Sequence& second_vector)
{
    int first_size = first_vector.size();
    int second_size = second_vector.size();
    std::vector<int> previous_line;

    for (int first_subsequence_index = 0; first_subsequence_index <= first_size; 
        ++first_subsequence_index) {
        std::vector<int> line;
        for (int second_subsequence_index = 0; second_subsequence_index <= second_size; 
            ++second_subsequence_index)
        if (second_subsequence_index == 0 || first_subsequence_index == 0) {
            line.push_back(std::max(first_subsequence_index, second_subsequence_index));
        }
        else {
            if (first_vector[first_subsequence_index - 1] == 
                second_vector[second_subsequence_index - 1]) {
                line.push_back(std::min(previous_line[second_subsequence_index - 1],
                    std::min(line[second_subsequence_index - 1], 
                        previous_line[second_subsequence_index]) + 1));
            }
            else {
                line.push_back(std::min(line[second_subsequence_index - 1], 
                    previous_line[second_subsequence_index]) + 1);
            }
        }

        std::swap(previous_line, line);
    }

    return previous_line[second_size];
}
