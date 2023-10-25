#pragma once

// From: https://www.codeproject.com/Articles/3267/Implementing-a-Subject-Observer-Pattern-with-Templ
template <class T>
class Observer
{
public:
    virtual void update(T *observable)= 0;
};
