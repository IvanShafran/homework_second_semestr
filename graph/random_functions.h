#pragma once

#include <cstdlib>
#include <stdexcept>
#include <fstream>

template <class T>
T Rand(T begin, T end)
{
    if (begin >= end)
        throw std::range_error("Rand(): begin >= end");
    return begin + (rand() % (end - begin));
}

inline bool RandBool()
{
    return Rand(0, 2) == 1;
}

template <class Sequence>
Sequence RandSequence(size_t size, const Sequence& element_set)
{
    if (element_set.empty())
        throw std::runtime_error("RandSequence(): element_set is empty");

    Sequence result;
    result.resize(size);
    for (size_t i = 0; i < size; i++)
        result[i] = element_set[Rand<size_t>(0, element_set.size())];

    return result;
}
