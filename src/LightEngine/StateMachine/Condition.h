#pragma once

template <typename T>
class Transition;

template<typename T>
class Condition 
{
    bool Test(T* owner);

public:
    bool expected = true;

    virtual bool OnTest(T* owner) = 0;

    friend Transition<T>;
};

#include "Condition.inl"
