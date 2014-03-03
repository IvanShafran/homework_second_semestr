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
    SignedArray<int> bounds(-(distance + 1), distance + 1);
    bounds[1] = 0;

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

    return bounds;
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
void GetMiddlePart(Sequence& middle_part, Iterator begin, Iterator end)
{
    middle_part.resize(end - begin);
    int i = 0;
    while (begin != end) {
        middle_part[i++] = *begin;
        begin++;
    }

}

template <class Sequence, class Iterator, class ReverseIterator>
Sequence LCSGetSubsequence(Iterator first_begin, Iterator first_end,
    ReverseIterator first_reverse_begin, ReverseIterator first_reverse_end,
    Iterator second_begin, Iterator second_end, 
    ReverseIterator second_reverse_begin, ReverseIterator second_reverse_end, 
    int distance)
{
    Sequence result;

    if (first_begin == first_end || second_begin == second_end) {
        return result;
    }

    int first_size = first_end - first_begin;
    int second_size = second_end - second_begin;
    
    int bound_distance = (distance + 1) / 2;
    SignedArray<int> bounds = LCSBounds(first_begin, first_end, 
        second_begin, second_end, bound_distance);
    SignedArray<int> reverse_bounds = LCSBounds(first_reverse_begin, first_reverse_end,
        second_reverse_begin, second_reverse_end, distance - bound_distance);

    
    for (int i = bounds.GetLeftBound(); i <= bounds.GetRightBound(); i++)
        std::cout << bounds[i] << ' ';
    std::cout << std::endl;
    for (int i = reverse_bounds.GetLeftBound(); i <= reverse_bounds.GetRightBound(); i++)
        std::cout << reverse_bounds[i] << ' ';
    std::cout << std::endl;
    std::cout << "#########################";
    
    reverse_bounds.Reverse();
    reverse_bounds.Shift(first_size - second_size);

    int first_subsequence_begin = 0, first_subsequence_end = 0;
    int second_subsequence_begin = 0, second_subsequence_end = 0;
    for (int diagonal = std::max(bounds.GetLeftBound(), reverse_bounds.GetLeftBound()); 
        diagonal <= std::min(bounds.GetRightBound(), reverse_bounds.GetRightBound()); 
        diagonal++)
    if ((bounds[diagonal] + reverse_bounds[diagonal]) >= first_size)
    {
        first_subsequence_begin = first_size - reverse_bounds[diagonal];
        first_subsequence_end = bounds[diagonal];
        second_subsequence_begin = first_subsequence_begin - diagonal;
        second_subsequence_end = first_subsequence_end - diagonal;
        break;
    }    

    Sequence middle_part;
    GetMiddlePart(middle_part, first_begin + first_subsequence_begin,
        first_begin + first_subsequence_end);
    
    Sequence begin_part = LCSGetSubsequence<Sequence>(first_begin, first_begin + first_subsequence_begin,        
        first_reverse_end - first_subsequence_begin, first_reverse_end, 
        second_begin, second_begin + second_subsequence_begin,
        second_reverse_end - second_subsequence_begin, second_reverse_end, bound_distance);

    Sequence end_part = LCSGetSubsequence<Sequence>(first_begin + first_subsequence_end, first_end,        
        first_reverse_begin, first_reverse_end - first_subsequence_end,
        second_begin + second_subsequence_end, second_end,
        second_reverse_begin, second_reverse_end - second_subsequence_end, distance - bound_distance);

    AddFromTo(begin_part, result);
    AddFromTo(middle_part, result);
    AddFromTo(end_part, result);
    
    return result;    
}

template <class Sequence>
Sequence LCSGetSubsequence(const Sequence& first_sequence, const Sequence& second_sequence)
{
    int distance = LCSDistance(first_sequence, second_sequence);

    return LCSGetSubsequence<Sequence>(first_sequence.begin(), first_sequence.end(),
        first_sequence.rbegin(), first_sequence.rend(),
        second_sequence.begin(), second_sequence.end(),
        second_sequence.rbegin(), second_sequence.rend(), distance);
}
