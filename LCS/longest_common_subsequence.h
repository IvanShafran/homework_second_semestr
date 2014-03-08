#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

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

template <class Sequence>
int LCSDistance(const Sequence& first_sequence, const Sequence& second_sequence)
{
    if ((first_sequence.size() == 0) || (second_sequence.size() == 0))
        return std::max(first_sequence.size(), second_sequence.size());

    size_t first_size = first_sequence.size(), second_size = second_sequence.size();
    int total_size = first_size + second_size;

    SignedArray<int> bounds(-total_size, total_size);
    bounds[1] = 0;

    for (int bound = 0; bound <= total_size; bound++)
    for (int diagonal = -bound; diagonal <= bound; diagonal += 2) {
        size_t x;
        if (diagonal == -bound || (diagonal != bound
            && bounds[diagonal - 1] < bounds[diagonal + 1]))
            x = bounds[diagonal + 1];
        else
            x = bounds[diagonal - 1] + 1;

        size_t y = x - diagonal;

        if (x <= first_size && y <= second_size) {
            int common_prefix_length = CommonPrefixLength(first_sequence.begin() + x, first_sequence.end(),
                second_sequence.begin() + y, second_sequence.end());
            x += common_prefix_length;
            y += common_prefix_length;
        }
        bounds[diagonal] = x;

        if (x >= first_size && y >= second_size) {
            return bound;
        }
    }
}

template <class Iterator>
SignedArray<int> LCSBounds(Iterator first_begin, Iterator first_end,
    Iterator second_begin, Iterator second_end, int distance)
{
    SignedArray<int> bounds(-(distance ), (distance ), 0);
    
    if (distance == 0)
    {
        bounds[0] = CommonPrefixLength(first_begin, first_end, 
            second_begin, second_end);
        return bounds;
    }

    for (int bound = 0; bound <= distance; bound++)
    for (int diagonal = -bound; diagonal <= bound; diagonal += 2) {
        int x;
        if (diagonal == -bound || (diagonal != bound
            && bounds[diagonal - 1] < bounds[diagonal + 1]))
            x = bounds[diagonal + 1];
        else
            x = bounds[diagonal - 1] + 1;

        int y = x - diagonal;
        
        if ((first_end - first_begin) >= x && (second_end - second_begin) >= y) {
            int common_prefix_length = CommonPrefixLength(first_begin + x, first_end,
                second_begin + y, second_end);
            x += common_prefix_length;
            y += common_prefix_length;
        }

        bounds[diagonal] = x;
    }

    return std::move(bounds);
}

template<class Sequence>
void AddFromTo(const Sequence& increament, Sequence& result)
{
    int result_size = result.size();
    result.resize(result_size + increament.size());
    for (int i = 0; i < increament.size(); i++)
        result[i + result_size] = increament[i];
}

template <class Sequence, class Iterator>
void PushCommonSubsequence(Sequence& sequence, Iterator begin, Iterator end)
{
    int additive_size = end - begin;
    if (additive_size <= 0)
        return;
    int primary_size = sequence.size();
    sequence.resize(primary_size + additive_size);
    int i = primary_size;
    while (begin != end) {
        sequence[i++] = *begin;
        begin++;
    }
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

    std::reverse_iterator<Iterator> first_reverse_begin(first_end),
        first_reverse_end(first_begin), second_reverse_begin(second_end),
        second_reverse_end(second_begin);

    if (distance == 0) {
        PushCommonSubsequence(result, first_begin, first_end);
        return result;
    }

    if (distance == 1)
    {
        int begin_common_sequence = CommonPrefixLength(first_begin, first_end,
            second_begin, second_end);
        int end_common_sequence = CommonPrefixLength(first_reverse_begin, 
            first_reverse_end - begin_common_sequence,
            second_reverse_begin, second_reverse_end - begin_common_sequence);
        PushCommonSubsequence(result, 
            first_begin, first_begin + begin_common_sequence);
        PushCommonSubsequence(result, 
            first_begin + first_size - end_common_sequence, first_end);
        return result;
    }
    
    int bound_distance = (distance + 1) / 2;
    SignedArray<int> bounds = LCSBounds(first_begin, first_end, 
        second_begin, second_end, bound_distance);
    SignedArray<int> reverse_bounds = LCSBounds(first_reverse_begin, first_reverse_end,
        second_reverse_begin, second_reverse_end, distance - bound_distance);

    reverse_bounds.Reverse();
    reverse_bounds.Shift(first_size - second_size);

    int first_subsequence_begin, second_subsequence_begin;
    for (int diagonal = std::max(bounds.GetLeftBound(), reverse_bounds.GetLeftBound()); 
        diagonal <= std::min(bounds.GetRightBound(), reverse_bounds.GetRightBound()); 
        diagonal++)
    if ((bounds[diagonal] + reverse_bounds[diagonal]) >= first_size)
    {
        first_subsequence_begin = first_size - reverse_bounds[diagonal];
        second_subsequence_begin = first_subsequence_begin - diagonal;
        break;
    }    

    Sequence begin_part = LCSGetSubsequence<Sequence>(first_begin, first_begin + first_subsequence_begin,        
        second_begin, second_begin + second_subsequence_begin, bound_distance);

    Sequence end_part = LCSGetSubsequence<Sequence>(first_begin + first_subsequence_begin, first_end,        
        second_begin + second_subsequence_begin, second_end, distance - bound_distance);

    AddFromTo(begin_part, result);
    AddFromTo(end_part, result);
    
    return result;    
}

template <class Sequence>
Sequence LCSGetSubsequence(const Sequence& first_sequence, const Sequence& second_sequence)
{
    int distance = LCSDistance(first_sequence, second_sequence);

    return LCSGetSubsequence<Sequence>
        (first_sequence.begin(), first_sequence.end(), second_sequence.begin(), second_sequence.end(), distance);
}
