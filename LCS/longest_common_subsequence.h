#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

template <class Iterator>
int CommonPrefixLength(Iterator first_begin, Iterator first_end,
    Iterator second_begin, Iterator second_end)
{
    size_t length = 0;
    while ((first_begin != first_end) && (second_begin != second_end) 
        && (*first_begin) == (*second_begin)) {
        ++first_begin;
        ++second_begin;
        length++;
    }
    return length;
}

template <class Sequence>
int LCSDistance(const Sequence& first_sequence, const Sequence& second_sequence)
{
    if ((first_sequence.size() == 0) || (second_sequence.size() == 0))
        return std::max(first_sequence.size(), second_sequence.size());

    size_t first_size = first_sequence.size(), second_size = second_sequence.size();
    std::vector<size_t> bounds;
    bounds.resize(2 * (first_size + second_size) + 1);
    int shift = (first_size + second_size);

    bounds[1 + shift] = 0;

    for (int bound = 0; bound <= (first_size + second_size); bound++)
    for (int diagonal = -bound; diagonal <= bound; diagonal += 2) {
        size_t x;
        if (diagonal == -bound || (diagonal != bound
            && bounds[diagonal - 1 + shift] < bounds[diagonal + 1 + shift]))
            x = bounds[diagonal + 1 + shift];
        else
            x = bounds[diagonal - 1 + shift] + 1;

        size_t y = x - diagonal;

        if (x <= first_size && y <= second_size) {
            int common_prefix_length = CommonPrefixLength(first_sequence.begin() + x, first_sequence.end(),
                second_sequence.begin() + y, second_sequence.end());
            x += common_prefix_length;
            y += common_prefix_length;
        }
        bounds[diagonal + shift] = x;

        if (x >= first_size && y >= second_size) {
            return bound;
        }
    }
}

template <class Iterator>
std::vector<size_t> LCSBounds(Iterator first_begin, Iterator first_end,
    Iterator second_begin, Iterator second_end, size_t distance)
{
    std::vector<size_t> bounds;
    bounds.resize(2 * distance + 1);
    int shift = distance;

    bounds[1 + shift] = 0;

    for (int bound = 0; bound <= distance; bound++)
    for (int diagonal = -bound; diagonal <= bound; diagonal += 2) {
        size_t x;
        if (diagonal == -bound || (diagonal != bound
            && bounds[diagonal - 1 + shift] < bounds[diagonal + 1 + shift]))
            x = bounds[diagonal + 1 + shift];
        else
            x = bounds[diagonal - 1 + shift] + 1;

        size_t y = x - diagonal;
        
        if ((first_end - first_begin) >= x && (second_end - second_begin) >= y) {
            int common_prefix_length = CommonPrefixLength(first_begin + x, first_end,
                second_begin + y, second_end);
            x += common_prefix_length;
            y += common_prefix_length;
        }

        bounds[diagonal + shift] = x;
    }

    return bounds;
}

/*
template <class Sequence, class Iterator>
Sequence LCSubsequence(Iterator first_begin, Iterator first_end, 
    Iterator first_reverse_begin, Iterator first_reverse_end,
    Iterator second_begin, Iterator second_end, Iterator second_reverse_begin,
    Iterator second_reverse_end, int distance)
{

}

template <class Sequence>
Sequence LCSubsequence(const Sequence& first_sequence, const Sequence& second_sequence)
{
    int distance = LCSDistance(first_sequence, second_sequence);
    
    return LCSubsequence();
}
*/