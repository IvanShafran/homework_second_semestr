#pragma once

#include <stdexcept>

template <class T>
class SignedArray{
    int left_bound_, right_bound_;
    int shift_;
    std::vector<T> array_;

    void Initialize(int left_bound, int right_bound)
    {
        shift_ = left_bound;
        left_bound_ = left_bound;
        right_bound_ = right_bound;
        array_.resize(right_bound - left_bound + 1);
    }

    void Initialize(SignedArray<T>& signed_array)
    {
        shift_ = signed_array.shift_;
        left_bound_ = signed_array.left_bound_;
        right_bound_ = signed_array.right_bound_;
        array_ = signed_array.array_;
    }

    void InitialazeData(T init_value)
    {
        for (int i = left_bound_; i <= right_bound_; i++)
            signed_array_[i] = init_value;
    }

    int GetIndex(int index)
    {
        return index - shift_;
    }

public:
    SignedArray(int left_bound, int right_bound)
    {
        if (left_bound > right_bound)
            throw std::range_error("SignedArray: left_bound > right_bound");
        
        Initialize(left_bound, right_bound);
    }

    SignedArray(int left_bound, int right_bound, T init_value)
    {
        if (left_bound > right_bound)
            throw std::range_error("SignedArray: left_bound > right_bound");

        Initialize(left_bound, right_bound);
        InitialazeData(init_value);
    }
    
    SignedArray(SignedArray<T>& signed_array)
    {
        
        Initialize(signed_array);
    }
    
    int GetLeftBound()
    {
        return left_bound_;
    }

    int GetRightBound()
    {
        return right_bound_;
    }

    size_t Size()
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
        left_bound_ += shift;
        right_bound_ += shift;
    }
    
    T& operator [] (int index) {
        if (index < left_bound_ || index > right_bound_)
            throw std::range_error("SignedArray: index not in [left_bound, right_bound]");

        return array_[GetIndex(index)];
    }   

    T operator [] (int index) const {
        if (index < left_bound_ || index > right_bound_)
            throw std::range_error("SignedArray: index not in [left_bound, right_bound]");

        return array_[GetIndex(index)];
    }
};
