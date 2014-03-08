#pragma once

#include <stdexcept>

template <class T>
class SignedArray{
    size_t size_;
    int left_bound_, right_bound_;
    int reverse_, shift_;
    T* array_;
    T* signed_array_;

    void Initialize(int left_bound, int right_bound)
    {
        reverse_ = 1;
        shift_ = 0;
        left_bound_ = left_bound;
        right_bound_ = right_bound;
        size_ = right_bound - left_bound + 1;

        array_ = new T[size_];
        signed_array_ = array_ - left_bound;
    }

    void Initialize(SignedArray<T>& signed_array)
    {
        reverse_ = signed_array.reverse_;
        shift_ = signed_array.shift_;
        left_bound_ = signed_array.left_bound_;
        right_bound_ = signed_array.right_bound_;
        size_ = right_bound_ - left_bound_ + 1;

        array_ = new T[size_];
        signed_array_ = array_ - left_bound_;
    }

    void InitialazeData(T init_value)
    {
        for (int i = left_bound_; i <= right_bound_; i++)
            signed_array_[i] = init_value;
    }

    void InitialazeData(SignedArray<T>& signed_array)
    {
        for (int i = left_bound_; i <= right_bound_; i++)
            signed_array_[i] = signed_array[i];
    }

    int GetIndex(int index)
    {
        return (index - shift_) * reverse_;
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
        InitialazeData(signed_array);
    }
    
    ~SignedArray()
    {
        delete [] array_;
    }
    
    int GetLeftBound()
    {
        return left_bound_;
    }

    int GetRightBound()
    {
        return right_bound_;
    }

    void Reverse()
    {
        reverse_ = -reverse_;
        shift_ *= reverse_;
        std::swap(left_bound_, right_bound_);
        left_bound_ *= -1;
        right_bound_ *= -1;
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
        return signed_array_[GetIndex(index)];
    }   

    T operator [] (int index) const {
        if (index < left_bound_ || index > right_bound_)
            throw std::range_error("SignedArray: index not in [left_bound, right_bound]");
        return signed_array_[GetIndex(index)];
    }
};
