#pragma once

#include <cstdlib>
#include <stdexcept>
#include <vector>

inline int Rand(int begin, int end)
{
    if (begin >= end)
        throw std::range_error("Rand(): begin >= end");
    return begin + (rand() % (end - begin));
}

inline std::string RandString(int length, const std::string& symbol_set)
{
    if (length < 0)
        throw std::length_error("RandString(): length < 0");
    if (symbol_set.length() == 0)
        throw std::runtime_error("RandString(): symbol_set is empty");

    std::string result;
    result.resize(length);
    for (size_t i = 0; i < length; i++)
        result[i] = symbol_set[Rand(0, symbol_set.length())];

    return result;
}

template <class T>
std::vector<T> RandVector(int size, const std::vector<T>& element_set)
{
    if (size < 0)
        throw std::length_error("RandVector(): size < 0");
    if (element_set.size() == 0)
        throw std::runtime_error("RandVector(): element_set is empty");

    std::vector<T> result;
    for (int i = 0; i < size; i++)
        result.push_back(element_set[Rand(0, element_set.size())]);

    return result;
}
