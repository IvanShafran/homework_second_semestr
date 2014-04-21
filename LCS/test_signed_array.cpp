#include <vector>

#include "signed_array.h"

void TestSignedArray()
{
    SignedArray<int> signed_array(-1, 2);
    std::vector<int> vector({ 0, 1, 2, 3 });
    signed_array.SetData(vector);

    if (signed_array[-1] != 0 || signed_array[0] != 1 ||
        signed_array[1] != 2 || signed_array[2] != 3)
        throw std::runtime_error("Error on TestSignedArray: operator[]");
    
    if (signed_array.GetData() != vector)
        throw std::runtime_error("Error on TestSignedArray: GetData()");

    signed_array.Reverse();
    std::reverse(vector.begin(), vector.end());
    if (signed_array.GetData() != vector)
        throw std::runtime_error("Error on TestSignedArray: Reverse()");

    signed_array.Shift(-1);
    if (signed_array[-2] != 3 || signed_array[-1] != 2 ||
        signed_array[0] != 1 || signed_array[1] != 0)
        throw std::runtime_error("Error on TestSignedArray: Shift()");

    if (signed_array.GetLeftBound() != -2)
        throw std::runtime_error("Error on TestSignedArray: GetLeftBound()");

    if (signed_array.GetRightBound() != 1)
        throw std::runtime_error("Error on TestSignedArray: GetRightBound()");

    if (signed_array.Size() != 4)
        throw std::runtime_error("Error on TestSignedArray: Size()");
}
