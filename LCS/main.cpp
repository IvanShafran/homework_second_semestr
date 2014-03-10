#include <iostream>
#include "test_longest_common_substring_distance.h"
#include "test_longest_common_subsequence_distance.h"
#include "test_common_prefix_length.h"
#include "test_lcs_get_substring.h"
#include "test_files_conversion.h"

int main()
{
    try {
        TestCommonPrefixLength();
        std::cout << "TestCommonPrefixLength OK" << std::endl;
        TestLCSubstringDistance();
        std::cout << "TestLCSubstringDistance OK" << std::endl;
        TestLCSubsequenceDistance();
        std::cout << "TestLCSubsequenceDistance OK" << std::endl;
        TestLCSGetSubstring();
        std::cout << "TestLCSGetSubstring OK" << std::endl;
        TestFilesÑonversion();
        std::cout << "TestFilesConversion OK" << std::endl;
        system("PAUSE");
        return 0;
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        system("PAUSE");
        return -1;
    }
}
