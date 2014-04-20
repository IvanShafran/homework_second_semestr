#pragma once

#include <cstdlib>
#include <stdexcept>
#include <fstream>

inline int Rand(int begin, int end)
{
    if (begin >= end)
        throw std::range_error("Rand(): begin >= end");
    return begin + (rand() % (end - begin));
}

template <class Sequence>
Sequence RandSequence(size_t size, const Sequence& element_set)
{
    if (element_set.empty())
        throw std::runtime_error("RandSequence(): element_set is empty");

    Sequence result;
    result.resize(size);
    for (int i = 0; i < size; i++)
        result[](element_set[Rand(0, element_set.size())]);

    return result;
}
