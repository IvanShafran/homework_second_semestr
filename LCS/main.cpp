#include <iostream>
#include <stdexcept>
#include "files_conversion.h"

void Usage()
{
    // @review: В usage обычно не используют запятые.
    // @review: Для вывода по-умолчанию как правило удобнее использовать стандартный поток вывода.
    // @review: conversin -> conversion
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
        // @review: У класса std::string есть implicit конструктор от const char*, поэтому
        // @review: static_cast<> здесь можно не писать:
        // @review:  GetDifference(argv[1], argv[2]);
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
