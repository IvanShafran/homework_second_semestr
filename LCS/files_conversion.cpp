#include <fstream>
#include <map>
#include <vector>
#include <string>

#include "longest_common_subsequence.h"
#include "random_functions.h"

void ReadFile(std::ifstream& file, std::vector<size_t>& sequence,  
    std::map<std::string, size_t>& get_key,
    std::map<size_t, std::string>& get_string, size_t& key)
{
    while (!file.eof()) {
        std::string line;
        std::getline(file, line);

        if (get_key.find(line) == get_key.end()) {
            key++;
            get_key[line] = key;
            get_string[key] = line;
        }

        sequence.push_back(get_key[line]);
    }
}

template <class Iterator>
void WriteLine(std::ofstream& file, std::map<size_t, std::string>& get_string,
    Iterator iterator, std::string addition)
{
    file << addition << get_string[*iterator] << std::endl;
}

void WriteConversion(std::vector<size_t>& first_sequence, 
    std::vector<size_t>& second_sequence, std::vector<size_t>& subsequence, 
    std::map<size_t, std::string>& get_string)
{
    std::ofstream file("conversion.txt");

    auto first_iterator = first_sequence.begin();
    auto second_iterator = second_sequence.begin();
    auto subsequence_iterator = subsequence.begin();

    while (first_iterator != first_sequence.end() &&
        second_iterator != second_sequence.end() &&
        subsequence_iterator != subsequence.end()) {

        if (*first_iterator == *second_iterator
            && *second_iterator == *subsequence_iterator) {
            WriteLine(file, get_string, first_iterator, "");
            first_iterator++;
            second_iterator++;
            subsequence_iterator++;
        }
        else if (*second_iterator == *subsequence_iterator) {
            WriteLine(file, get_string, first_iterator, "- ");
            first_iterator++;
        }
        else {
            WriteLine(file, get_string, second_iterator, "+ ");
            second_iterator++;
        }
    }

    if (subsequence_iterator != subsequence.end())
        throw std::logic_error("WriteConversion: Wrong common subsequence");

    while (first_iterator != first_sequence.end()) {
        WriteLine(file, get_string, first_iterator, "- ");
        first_iterator++;
    }

    while (second_iterator != second_sequence.end()) {
        WriteLine(file, get_string, second_iterator, "+ ");
        second_iterator++;
    }
}

void FilesConverison()
{
    std::ifstream first_file("first_file.txt");
    std::ifstream second_file("second_file.txt");

    std::map<std::string, size_t> get_key;
    std::map<size_t, std::string> get_string;
    std::vector<size_t> first_sequence;
    std::vector<size_t> second_sequence;
    size_t key = 0;

    ReadFile(first_file, first_sequence, get_key, get_string, key);
    ReadFile(second_file, second_sequence, get_key, get_string, key);

    std::vector<size_t> common_subsequence = 
        LCSGetSubsequence(first_sequence, second_sequence);

    WriteConversion(first_sequence, second_sequence, 
        common_subsequence, get_string);
}

template <class Iterator>
bool equal_sequence(Iterator first_begin, Iterator first_end,
    Iterator second_begin, Iterator second_end)
{
    if ((first_end - first_begin) != (second_end - second_begin))
        return false;
    return CommonPrefixLength(first_begin, first_end, 
        second_begin, second_end) == (first_end - first_begin);
}

void CheckConversion(std::string error_text)
{
    std::ifstream first_file("first_file.txt");
    std::ifstream second_file("second_file.txt");
    std::ifstream conversion("conversion.txt");

    std::string first_line;
    std::string second_line;
    std::string line;

    std::getline(first_file, first_line);
    std::getline(second_file, second_line);

    while (!conversion.eof()) {
        std::getline(conversion, line);

        if (line[0] == '+') {
            if (!equal_sequence(line.begin() + 2, line.end(),
                second_line.begin(), second_line.end()))
                throw std::runtime_error("Error: " + error_text);
            std::getline(second_file, second_line);
        }
        else if (line[0] == '-') {
            if (!equal_sequence(line.begin() + 2, line.end(),
                first_line.begin(), first_line.end()))
                throw std::runtime_error("Error: " + error_text);
            std::getline(first_file, first_line);
        }
        else {
            if ((line != first_line) || (line != second_line))
                throw std::runtime_error("Error: " + error_text);
            std::getline(first_file, first_line);
            std::getline(second_file, second_line);
        }
    }

    if (!first_file.eof() || !second_file.eof())
        throw std::runtime_error("Error: " + error_text);
}

void TestFiles—onversion(int count_iterations, int min_file_size, int max_file_size, 
    int min_line_size, int max_line_size, std::string symbol_set, std::string error_text)
{
    srand(777);
    for (int i = 0; i < count_iterations; i++)
    {
        int first_size = Rand(min_file_size, max_file_size);
        int second_size = Rand(min_file_size, max_file_size);
        RandFile("first_file.txt", first_size, min_line_size, max_line_size, symbol_set);
        RandFile("second_file.txt", second_size, min_line_size, max_line_size, symbol_set);

        FilesConverison();
        CheckConversion(error_text);
    }
}


void TestFiles—onversion()
{
    TestFiles—onversion(10000, 0, 10, 0, 2, "ab", "TestFiles—onversion Small Size of File Test, Short lines");
    TestFiles—onversion(1000, 500, 1000, 0, 2, "ab", "TestFiles—onversion Medium Size of File Test, Short lines");
    TestFiles—onversion(50, 5000, 10000, 0, 2, "ab", "TestFiles—onversion Big Size of File Test, Short lines");
    TestFiles—onversion(1, 50000, 100000, 0, 4, "ab", "TestFiles—onversion Huge Size of File Test, Short lines");
    TestFiles—onversion(100, 500, 1000, 50, 100, "abcdefg", "TestFiles—onversion Medium Size of File Test, Medium Size of lines");
    TestFiles—onversion(100, 500, 1000, 999, 1000, "abc", "TestFiles—onversion Medium Size of File Test, Long lines");
}
