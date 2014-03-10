#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "signed_array.h"

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

template <class Iterator>
std::pair<int, int> LCSDoStep(int bound, int diagonal, SignedArray<int>& bounds,
    Iterator first_begin, Iterator first_end, 
    Iterator second_begin, Iterator second_end)
{
    int first_size = first_end - first_begin;
    int second_size = second_end - second_begin;

    int x;
    if (diagonal == -bound || (diagonal != bound
        && bounds[diagonal - 1] < bounds[diagonal + 1]))
        x = bounds[diagonal + 1];
    else
        x = bounds[diagonal - 1] + 1;

    int y = x - diagonal;

    if (first_size >= x && second_size >= y) {
        int common_prefix_length = CommonPrefixLength(first_begin + x, first_end,
            second_begin + y, second_end);
        x += common_prefix_length;
        y += common_prefix_length;
    }

    bounds[diagonal] = x;

    return std::pair<int, int>(x, y);
}

template <class Sequence>
int LCSDistance(const Sequence& first_sequence, const Sequence& second_sequence)
{
    if ((first_sequence.size() == 0) || (second_sequence.size() == 0))
        return std::max(first_sequence.size(), second_sequence.size());

    int first_size = first_sequence.size(), second_size = second_sequence.size();
    int total_size = first_size + second_size;

    SignedArray<int> bounds(-total_size, total_size);
    bounds[1] = 0;

    for (int bound = 0; bound <= total_size; bound++)
    for (int diagonal = -bound; diagonal <= bound; diagonal += 2) {
        std::pair<int, int> position = LCSDoStep(bound, diagonal, bounds, 
            first_sequence.begin(), first_sequence.end(),
            second_sequence.begin(), second_sequence.end());

        if (position.first >= first_size && position.second >= second_size) {
            return bound;
        }
    }
}

template <class Iterator>
SignedArray<int> LCSBounds(Iterator first_begin, Iterator first_end,
    Iterator second_begin, Iterator second_end, int distance)
{
    SignedArray<int> bounds(-distance, distance);
    
    if (distance == 0) {
        bounds[0] = CommonPrefixLength(first_begin, first_end, 
            second_begin, second_end);
        return bounds;
    }

    bounds[1] = 0;

    for (int bound = 0; bound <= distance; bound++)
    for (int diagonal = -bound; diagonal <= bound; diagonal += 2) 
        LCSDoStep(bound, diagonal, bounds, first_begin, first_end,
            second_begin, second_end);    

    return bounds;
}

template <class Iterator>
std::pair<int, int> LCSGetSeparator(int distance, 
    Iterator first_begin, Iterator first_end, 
    Iterator second_begin, Iterator second_end)
{
    int bound_distance = (distance + 1) / 2;
    int first_size = first_end - first_begin;
    int second_size = second_end - second_begin;
    std::reverse_iterator<Iterator> first_reverse_begin(first_end),
        first_reverse_end(first_begin), second_reverse_begin(second_end),
        second_reverse_end(second_begin);

    SignedArray<int> bounds = LCSBounds(first_begin, first_end,
        second_begin, second_end, bound_distance);
    SignedArray<int> reverse_bounds = LCSBounds(first_reverse_begin, first_reverse_end,
        second_reverse_begin, second_reverse_end, distance - bound_distance);

    reverse_bounds.Reverse();
    reverse_bounds.Shift(first_size - second_size);

    int first_subsequence_begin, second_subsequence_begin;
    int min_index = std::max(bounds.GetLeftBound(), reverse_bounds.GetLeftBound());
    int max_index = std::min(bounds.GetRightBound(), reverse_bounds.GetRightBound());
    for (int diagonal = min_index; diagonal <= max_index; diagonal++)
    if ((bounds[diagonal] + reverse_bounds[diagonal]) >= first_size)
    {
        first_subsequence_begin = first_size - reverse_bounds[diagonal];
        second_subsequence_begin = first_subsequence_begin - diagonal;
        break;
    }

    return std::pair<int, int>(first_subsequence_begin, second_subsequence_begin);
}

template <class Sequence, class Iterator>
Sequence LCSGetSubsequence(Iterator first_begin, Iterator first_end,
    Iterator second_begin, Iterator second_end, 
    int distance)
{    
    Sequence result;
    int first_size = first_end - first_begin;
    int second_size = second_end - second_begin;

    if (first_begin == first_end || second_begin == second_end) {
        return result;
    }

    if (distance == 0) {
        result.insert(result.end(), first_begin, first_end);
        return result;
    }

    if (distance == 1) {
        std::reverse_iterator<Iterator> first_reverse_begin(first_end),
            first_reverse_end(first_begin), second_reverse_begin(second_end),
            second_reverse_end(second_begin);

        int begin_common_sequence = CommonPrefixLength(first_begin, first_end,
            second_begin, second_end);
        int end_common_sequence = CommonPrefixLength(first_reverse_begin, 
            first_reverse_end - begin_common_sequence,
            second_reverse_begin, second_reverse_end - begin_common_sequence);
        result.insert(result.end(), first_begin, first_begin + begin_common_sequence);
        result.insert(result.end(), first_begin + first_size - end_common_sequence, first_end);
        return result;
    }
    
    int bound_distance = (distance + 1) / 2;    
    std::pair<int, int> separator = LCSGetSeparator(distance, first_begin, first_end, 
        second_begin, second_end);

    Sequence begin_part = LCSGetSubsequence<Sequence>(first_begin, first_begin + separator.first,
        second_begin, second_begin + separator.second, bound_distance);

    Sequence end_part = LCSGetSubsequence<Sequence>(first_begin + separator.first, first_end,
        second_begin + separator.second, second_end, distance - bound_distance);

    result.insert(result.end(), begin_part.begin(), begin_part.end());
    result.insert(result.end(), end_part.begin(), end_part.end());
    return result;    
}

template <class Sequence>
Sequence LCSGetSubsequence(const Sequence& first_sequence, const Sequence& second_sequence)
{
    int distance = LCSDistance(first_sequence, second_sequence);

    return LCSGetSubsequence<Sequence>
        (first_sequence.begin(), first_sequence.end(), second_sequence.begin(), second_sequence.end(), distance);
}
