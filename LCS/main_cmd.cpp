#include <iostream>
#include <stdexcept>
#include <fstream>

#include "files_conversion.h"

void Usage()
{
    std::cout << "Usage: first_filename second_filename conversion_filename(conversion.txt by default)" << std::endl;

    std::exit(-1);
}

void GetDifference(const std::string& first_filename, const std::string& second_filename,
                   const std::string& difference_filename = "conversion.txt")
{
    std::ifstream first_stream(first_filename);
    std::ifstream second_stream(second_filename);
    std::ofstream difference_stream(difference_filename);

    DoFilesConverison(first_stream, second_stream, difference_stream);
}

int main__(int argc, const char** argv)
{
    std::ios_base::sync_with_stdio(false);

    if (argc == 3) {
        GetDifference(argv[1], argv[2]);
    }
    else
    if (argc == 4) {
        GetDifference(argv[1], argv[2], argv[3]);
    }
    else {
        Usage();
    }

    return 0;
}
