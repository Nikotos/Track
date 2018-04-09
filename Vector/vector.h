#ifndef EXTRAPOLATION_VECTOR_H
#define EXTRAPOLATION_VECTOR_H

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <iostream>

using namespace std;

/* -------------------------------------------------------
 *  My own Vector
 *
 *
 *
 /------------------------------------------------------*/


template <typename DataT>
class Vector {
private:
    DataT* buffer_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

public:
    Vector() {};

    explicit inline Vector(size_t capacity);

    inline Vector(const Vector& that);

    inline Vector(Vector&& victim);

    inline ~Vector();

    inline DataT& operator[] (int pos);

    inline Vector& operator = (Vector victim) {
        swap(victim);
        printf("I am [ = operator] for long-live objects work with [%d] size\n", victim.capacity_);
    }

    inline Vector& operator = (Vector&& victim) {
        swap(victim);
        printf("I am [ = operator] for short-live objects work with [%d] size\n", victim.capacity_);
    }

    inline void swap(Vector& that);

};


#include "vector.cpp"

#ifdef LAB_KILLER
#include "vector_labs.cpp"
#endif //LAB_KILLER



#endif //EXTRAPOLATION_VECTOR_H