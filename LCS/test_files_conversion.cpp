#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include "random_functions.h"
#include "files_conversion.h"

void CheckConversion(std::istream& first_stream, std::istream& second_stream,
    std::istream& difference_stream, const std::string& error_text)
{
    std::string first_line;
    std::string second_line;
    std::string line;

    std::getline(first_stream, first_line);
    std::getline(second_stream, second_line);

    if (first_stream.bad() || second_stream.bad())
        throw std::runtime_error("Error while reading stream:" + error_text);

    while (!difference_stream.eof()) {
        std::getline(difference_stream, line);
        if (difference_stream.bad())
            break;

        if (line[0] == '+') {
            if (!std::equal(line.begin() + 1, line.end(), 
                second_line.begin()))
                throw std::runtime_error("Error: " + error_text);
            std::getline(second_stream, second_line);
        }
        else if (line[0] == '-') {
            if (!std::equal(line.begin() + 1, line.end(), 
                first_line.begin()))
                throw std::runtime_error("Error: " + error_text);
            std::getline(first_stream, first_line);
        }
        else {
            if ((line != first_line) || (line != second_line))
                throw std::runtime_error("Error: " + error_text);
            std::getline(first_stream, first_line);
            std::getline(second_stream, second_line);
        }

        if (first_stream.bad() || second_stream.bad())
            break;
    }

    if (difference_stream.bad() || first_stream.bad() || second_stream.bad())
        throw std::runtime_error("Error while reading stream:" + error_text);

    if (!first_stream.eof() || !second_stream.eof())
        throw std::runtime_error("Error: " + error_text);
}

void TestFilesConversion(int count_iterations, int min_file_size, 
    int max_file_size, int min_line_size, int max_line_size, 
    const std::string& symbol_set, const std::string& error_text)
{
    srand(777);
    for (int i = 0; i < count_iterations; i++)
    {
        int first_size = Rand(min_file_size, max_file_size);
        int second_size = Rand(min_file_size, max_file_size);
        std::string first_string;
        std::string second_string;
        {
            std::ostringstream ofirst_stream(first_string);
            std::ostringstream osecond_stream(second_string);
            RandStream(ofirst_stream, first_size, min_line_size,
                max_line_size, symbol_set);
            RandStream(osecond_stream, second_size, min_line_size,
                max_line_size, symbol_set);
        }

        std::string difference;
        {
            std::istringstream ifirst_stream(first_string);
            std::istringstream isecond_stream(second_string);
            std::ostringstream odifference_stream(difference);

            DoFilesConverison(ifirst_stream, isecond_stream, odifference_stream);
        }

        std::istringstream ifirst_stream(first_string);
        std::istringstream isecond_stream(second_string);
        std::istringstream idifference_stream(difference);

        CheckConversion(ifirst_stream, isecond_stream, idifference_stream, 
            error_text);
    }
}

void TestFilesConversion()
{
    TestFilesConversion(1000, 0, 10, 0, 2, "ab", "TestFilesConversion Small Size of File Test, Short lines");
    TestFilesConversion(100, 50, 100, 0, 2, "ab", "TestFilesConversion Medium Size of File Test, Short lines");
    TestFilesConversion(50, 500, 1000, 0, 2, "ab", "TestFilesConversion Big Size of File Test, Short lines");
    TestFilesConversion(1, 5000, 10000, 0, 4, "ab", "TestFilesConversion Huge Size of File Test, Short lines");
    TestFilesConversion(100, 50, 100, 250, 500, "abcdefg", "TestFilesConversion Medium Size of File Test, Medium Size of lines");
    TestFilesConversion(100, 50, 100, 2500, 5000, "abc", "TestFilesConversion Medium Size of File Test, Long lines");
}
