#include <iostream>
#include "test_longest_common_substring_distance.h"
#include "test_longest_common_subsequence_distance.h"
#include "test_common_prefix_length.h"
#include "test_longest_common_subsequence_bounds.h"

int main()
{
    try {
        //TestCommonPrefixLength();
        //TestLCSubstring();
        //TestLCSubsequence();
        TestLCSBounds();
        system("PAUSE");
        return 0;
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        system("PAUSE");
        return -1;
    }
}
