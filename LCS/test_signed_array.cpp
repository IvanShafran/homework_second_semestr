#include <vector>

#include "signed_array.h"

void TestSignedArray()
{
    SignedArray<int> signed_array(-1, 2);
    std::vector<int> vector({ 0, 1, 2, 3 });
    signed_array = vector;
    
    // @review: Хорошо бы проверить и остальные методы тоже.

    if (signed_array[-1] != 0 || signed_array[0] != 1 ||
        signed_array[1] != 2 || signed_array[2] != 3)
        throw std::runtime_error("Error on TestSignedArray: operator[]");
    
    signed_array.Reverse();
    std::reverse(vector.begin(), vector.end());
    if (signed_array.GetData() != vector)
        throw std::runtime_error("Error on TestSignedArray: Reverse()");

    signed_array.Shift(-1);
    if (signed_array[-2] != 3 || signed_array[-1] != 2 ||
        signed_array[0] != 1 || signed_array[1] != 0)
        throw std::runtime_error("Error on TestSignedArray: Shift()");
}
