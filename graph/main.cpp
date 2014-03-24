#include <iostream>
#include <stdexcept>

#include "unit_test.h"

int main()
{
    try {
        UnitTest();
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        system("PAUSE");
        return -1;
    }    
}
