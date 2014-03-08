#include <iostream>
#include "test_longest_common_substring_distance.h"
#include "test_longest_common_subsequence_distance.h"
#include "test_common_prefix_length.h"
#include "test_lcs_get_substring.h"

int main()
{
    try {
        //TestCommonPrefixLength();
        //TestLCSubstringDistance();
        //TestLCSubsequenceDistance();
        TestLCSGetSubstring();
        system("PAUSE");
        return 0;
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        system("PAUSE");
        return -1;
    }
}
