#include <iostream>

#include "test_longest_common_subsequence_distance.h"
#include "test_longest_common_substring_distance.h"
#include "test_common_prefix_length.h"
#include "test_find_longest_common_substring.h"
#include "test_files_conversion.h"
#include "test_files_conversion_by_file.h"
#include "test_signed_array.h"

int main()
{       
    std::ios_base::sync_with_stdio(false);
    try {
        TestCommonPrefixLength();
        std::cout << "TestCommonPrefixLength OK" << std::endl;
        TestLCSubstringDistance();
        std::cout << "TestLCSubstringDistance OK" << std::endl;
        TestLCSubsequenceDistance();
        std::cout << "TestLCSubsequenceDistance OK" << std::endl;
        TestFindLongestCommonSubsequence();
        std::cout << "TestFindLongestCommonSubsequence OK" << std::endl;
        TestFilesConversion();
        std::cout << "TestFilesConversion OK" << std::endl;
        TestFilesConversionByFile();
        std::cout << "TestFilesConversionByFiles OK" << std::endl;
        TestSignedArray();
        std::cout << "TestSignedArray OK" << std::endl;
        system("PAUSE");
        return 0;
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        system("PAUSE");
        return -1;
    }
}
