// @review: Если этот файл отвечает только за тестирование, то вероятно его стоит переименовать.
#include <fstream>
#include <string>

#include "random_functions.h"
#include "files_conversion.h"

template <class Iterator>
bool equal_sequence(Iterator first_begin, Iterator first_end,
    Iterator second_begin, Iterator second_end)
{
    if ((first_end - first_begin) != (second_end - second_begin))
        return false;
    return CommonPrefixLength(first_begin, first_end, 
        second_begin, second_end) == (first_end - first_begin);
}

// @review: Составные объекты нужно передавать по константной ссылке. Тогда будет меньше копирований.
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

    while (!conversion.eof()) {  // @review: В случае ошибки ввода получится бесконечный цикл.
        std::getline(conversion, line);

        if (line[0] == '+') {
            if (!equal_sequence(line.begin() + 1, line.end(),
                second_line.begin(), second_line.end()))
                throw std::runtime_error("Error: " + error_text);
            std::getline(second_file, second_line);
        }
        else if (line[0] == '-') {
            if (!equal_sequence(line.begin() + 1, line.end(),
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

void TestFilesConversion(int count_iterations, int min_file_size, int max_file_size, 
    int min_line_size, int max_line_size, std::string symbol_set, std::string error_text)
{
    srand(777);
    for (int i = 0; i < count_iterations; i++)
    {
        int first_size = Rand(min_file_size, max_file_size);
        int second_size = Rand(min_file_size, max_file_size);
        RandFile("first_file.txt", first_size, min_line_size, max_line_size, symbol_set);
        RandFile("second_file.txt", second_size, min_line_size, max_line_size, symbol_set);

        FilesConverison("first_file.txt", "second_file.txt", "conversion.txt");
        CheckConversion(error_text);
    }
}

void DoSimilarFiles(int size, int max_line_size, std::string symbol_set)
{
    RandFile("first_file.txt", size, 0, max_line_size, symbol_set);
    
    //generate similar second file
    std::ifstream first_file("first_file.txt");
    std::ofstream second_file("second_file.txt");

    srand(777);
    while (!first_file.eof()) {
        std::string line;
        std::getline(first_file, line);

        if ((rand() % 5) == 0)
            line = line + '-';
        second_file << line << std::endl;
    }

}

void TestFilesConversionSimilarFiles(int count_iterations, int max_file_size,
    int max_line_size, std::string symbol_set, std::string error_text)
{
    srand(777);
    for (int i = 0; i < count_iterations; i++)
    {
        int size = Rand(0, max_file_size);
        DoSimilarFiles(size, max_line_size, symbol_set);

        FilesConverison("first_file.txt", "second_file.txt", "conversion.txt");
        CheckConversion(error_text);
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
    
    TestFilesConversionSimilarFiles(100, 100, 100, "abcdefgh", "TestFilesConversionSimilarFiles");
    
}
