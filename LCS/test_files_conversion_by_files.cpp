#include <fstream>

#include "files_conversion.h"

void TestFilesConversionByFile()
{
    {
        std::ofstream first_stream("first.txt");
        first_stream << "a a" << std::endl;
        first_stream << "a b";

        std::ofstream second_stream("second.txt");
        second_stream << "a" << std::endl;
        second_stream << "a" << std::endl;
        second_stream << "a b";
    }

    {
    std::ifstream first_stream("first.txt");
    std::ifstream second_stream("second.txt");
    std::ofstream difference_stream("diff.txt");

    DoFilesConverison(first_stream, second_stream, difference_stream);
}


    {
        std::ifstream difference_stream("diff.txt");
        if (!difference_stream.is_open())
            throw std::runtime_error("error while opening file on TestFilesConversionByFile");

        std::string first_line, second_line, third_line, fourth_line, empty_line;

        std::getline(difference_stream, first_line); 
        std::getline(difference_stream, second_line);
        std::getline(difference_stream, third_line);
        std::getline(difference_stream, fourth_line);
        std::getline(difference_stream, empty_line);

        if (difference_stream.bad())
            throw std::runtime_error("Error on TestFilesConversionByFile: stream bad after reading");

        if (first_line != "+a" || second_line != "+a" || third_line != "-a a" 
            || fourth_line != "a b" || empty_line != ""
            || !difference_stream.eof())
            throw std::runtime_error("Error on on TestFilesConversionByFile: wrong common subsequence");

    }
}
