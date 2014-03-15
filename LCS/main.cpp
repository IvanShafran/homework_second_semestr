#include <iostream>
#include <stdexcept>
#include "files_conversion.h"

void Usage()
{
    std::cerr << "Usage: first_filename, second_filename, conversin_filename(conversion.txt by default)" << std::endl;
    std::exit(-1);
}

void GetDifference(std::string first_filename, std::string second_filename,
                   std::string difference_filename = "conversion.txt")
{
    FilesConverison(first_filename, second_filename, difference_filename);
}

int main(int argc, const char** argv)
{
    std::ios_base::sync_with_stdio(false);

    if (argc == 3) {
        GetDifference(static_cast<std::string>(argv[1]), static_cast<std::string>(argv[2]));
    }
    else
    if (argc == 4) {
        GetDifference(static_cast<std::string>(argv[1]), static_cast<std::string>(argv[2]), 
            static_cast<std::string>(argv[3]));
    }
    else {
        Usage();
    }

    return 0;
}
