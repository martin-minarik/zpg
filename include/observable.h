#pragma once

#include <vector>
#include <algorithm>

#include "observer.h"

// From: https://www.codeproject.com/Articles/3267/Implementing-a-Subject-Observer-Pattern-with-Templ

template<class T>
class Observable
{
public:
    void attach_observer(Observer<T> *observer)
    {
        observers.push_back(observer);
    }

    void detach_observer(Observer<T> *observer)
    {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end())
            observers.erase(it);
    }

    void notify_observers()
    {
        for (auto &observer: observers)
            observer->update(static_cast<T *> (this));
    }

private:
    std::vector<Observer<T> *> observers;
};


