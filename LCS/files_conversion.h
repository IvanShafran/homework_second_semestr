#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "longest_common_subsequence.h"

inline std::vector<std::string> ReadStream(std::istream& stream)
{
    std::vector<std::string> input_strings;
    while (!stream.eof())
    {
        std::string line;
        std::getline(stream, line);
        if (stream.bad())
            throw std::runtime_error("Error while reading of stream on DoFilesConversion:ReadStream");

        input_strings.push_back(line);
    }
    return input_strings;
}

inline std::vector<size_t> Integrise(const std::vector<std::string>& strings, 
    std::map<std::string, size_t>* string_map, 
    std::vector<std::string>* string_storage)
{
    std::vector<size_t> result;
    for (size_t i = 0; i < strings.size(); ++i)
    {
        if (string_map->find(strings[i]) == string_map->end()) {
            (*string_map)[strings[i]] = string_map->size();
            string_storage->push_back(strings[i]);
        }

        result.push_back((*string_map)[strings[i]]);
    }

    return result;
}

inline void WriteLine(std::ostream& stream, const std::string& addition,
    const std::string& line)
{
    stream << addition << line << std::endl;
}

inline void WriteConversion(std::ostream& difference_stream,
    const std::vector<size_t>& first_sequence,
    const std::vector<size_t>& second_sequence,
    const std::vector<size_t>& subsequence,
    const std::vector<std::string>& string_storage)
{
    auto first_iterator = first_sequence.begin();
    auto second_iterator = second_sequence.begin();
    auto subsequence_iterator = subsequence.begin();

    while (first_iterator != first_sequence.end() &&
        second_iterator != second_sequence.end() &&
        subsequence_iterator != subsequence.end()) {

        if (*first_iterator == *second_iterator
            && *second_iterator == *subsequence_iterator) {
            WriteLine(difference_stream, "", string_storage[*first_iterator]);
            ++first_iterator;
            ++second_iterator;
            ++subsequence_iterator;
        }
        else
        if (*second_iterator == *subsequence_iterator) {
            WriteLine(difference_stream, "-", string_storage[*first_iterator]);
            ++first_iterator;
        }
        else {
            WriteLine(difference_stream, "+", string_storage[*second_iterator]);
            ++second_iterator;
        }
    }

    if (subsequence_iterator != subsequence.end())
        throw std::runtime_error("WriteConversion: Wrong common subsequence");

    while (first_iterator != first_sequence.end()) {
        WriteLine(difference_stream, "-", string_storage[*first_iterator]);
        ++first_iterator;
    }

    while (second_iterator != second_sequence.end()) {
        WriteLine(difference_stream, "+", string_storage[*second_iterator]);
        ++second_iterator;
    }
}

inline void DoFilesConverison(std::istream& first_stream, std::istream& second_stream,
    std::ostream& difference_stream)
{
    std::map<std::string, size_t> string_map;
    std::vector<std::string> string_storage;

    std::vector<size_t> first_sequence;
    std::vector<size_t> second_sequence;

    {
        std::vector<std::string> first_string_sequence = ReadStream(first_stream);
        std::vector<std::string> second_string_sequence = ReadStream(second_stream);

        first_sequence = Integrise(first_string_sequence, &string_map, &string_storage);
        second_sequence = Integrise(second_string_sequence, &string_map, &string_storage);
    }

    std::vector<size_t> common_subsequence =
        FindLongestCommonSubsequence(first_sequence, second_sequence);

    WriteConversion(difference_stream, first_sequence, second_sequence,
        common_subsequence, string_storage);
}
