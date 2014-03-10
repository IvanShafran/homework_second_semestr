#pragma once

#include <stdexcept>

template <class T>
class SignedArray{
    int shift_;
    std::vector<T> array_;

    void Initialize(int left_bound, int right_bound, T value)
    {
        shift_ = left_bound;
        array_.resize(right_bound - left_bound + 1, value);
    }

    int GetIndex(int index)
    {
        return index - shift_;
    }

public:
    SignedArray(int left_bound, int right_bound, T value = 0)
    {
        if (left_bound > right_bound)
            throw std::range_error("SignedArray: left_bound > right_bound");

        Initialize(left_bound, right_bound, value);
    }
    
    int GetLeftBound() const
    {
        return shift_;
    }

    int GetRightBound() const
    {
        return array_.size() + shift_ - 1;
    }

    size_t Size() const
    {
        return array_.size();
    }

    void Reverse()
    {
        std::reverse(array_.begin(), array_.end());
    }

    void Shift(int shift)
    {
        shift_ += shift; 
    }
    
    T& operator [] (int index) {
        return array_.at(GetIndex(index));
    }   

    T operator [] (int index) const {
        return array_.at(GetIndex(index));
    }
};
