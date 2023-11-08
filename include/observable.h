#pragma once

//
// Created by Martin Minarik
//

#include <vector>
#include <algorithm>

#include "observer.h"


template<class T>
class Observable {
public:
    void attach_observer(Observer<T> *observer) {
        observers.push_back(observer);
    }

    void detach_observer(Observer<T> *observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end())
            observers.erase(it);
    }


    virtual void notify_observers() {
        for (auto &observer: observers)
            observer->update(static_cast<T *> (this));
    }

protected:
    void notify_observers(int descriptor) {
        for (auto &observer: observers)
            observer->update(static_cast<T *> (this), descriptor);
    }

private:
    std::vector<Observer<T> *> observers;
};


