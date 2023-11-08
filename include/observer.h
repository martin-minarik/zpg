#pragma once

//
// Created by Martin Minarik
//

template<class T>
class Observer {
public:
    virtual void update(T *observable) {

    }

    virtual void update(T *observable, int descriptor) {

    }
};
