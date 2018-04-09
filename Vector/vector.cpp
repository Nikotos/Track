#ifndef EXTRAPOLATION_VECTOR_CPP
#define EXTRAPOLATION_VECTOR_CPP


#include "vector.h"

/* -------------------------------------------------------
 *  @descr Constructor for Vector template class
 *         Construct Vector using needed capacity
 *
 *
 *  @note fill with start values
 /------------------------------------------------------*/
template <typename DataT>
inline Vector<DataT>::Vector(size_t capacity)                 //сделать выделение char массива
{
    buffer_  = new DataT [capacity];
    size_ = 0;
    capacity_ = capacity;
    printf("I am usuall constructor, I have filled buffer with raw chars \n");
}


/* -------------------------------------------------------
 *  @descr Copy Constructor for Vector template class
 *  Construct Vector using another Vector
 *
 *  @note for long-live objects
 /------------------------------------------------------*/
template <typename  DataT>
inline Vector<DataT>::Vector(const Vector& that)           // use std::copy
{
    Vector victim(that.capacity_);
    std::copy(victim.buffer_, that.buffer_, that.capacity_ );
    swap(victim);
    printf("I am copy constructor, creating object with size [%d]\n", that.capacity_);
};


/* -------------------------------------------------------
 *  @descr Copy operator for Vector
 *
 *  @note Specially for objects with short life
 *
 *
 /--------------------------------------------------------*/
template  <typename DataT>
inline Vector<DataT>::Vector(Vector&& victim):
        buffer_  (victim.buffer_),
        size_    (victim.size_),
        capacity_ (victim.capacity_)
{
    printf("I am weird stealing constructor\n");
    victim.buffer_ = nullptr;
}



/* -------------------------------------------------------
 *  @descr Destructor for Vector template class
 *
 *  @note Write about deleting objects to control the situation
 *
 /------------------------------------------------------*/
template  <typename DataT>
inline Vector<DataT>::~Vector()
{
    printf("I am Vector destructor, I have destructed Vector with capacity: [%d]\n", capacity_);
    printf("And Sizeof: [%d + %d] bytes\n", sizeof(DataT)*capacity_, sizeof(size_) + sizeof(capacity_));
    printf("\n");

    delete [] buffer_;
    buffer_ = nullptr;
    capacity_ = 0;
    size_ = 0;
}

template <typename DataT>
inline DataT& Vector<DataT>::operator[] (int pos) {
    assert(pos > -1);
    assert(pos < capacity_);

    return buffer_[pos];
}

/* -------------------------------------------------------
 *  @descr Swap procedure for move semantics
 *
 *
 *  @note swap all internal fields
 /------------------------------------------------------*/

template <typename DataT>
inline void Vector<DataT>::swap(Vector& that)
{
    std::swap(size_,that.size_);
    std::swap(capacity_, that.capacity_);
    std::swap(buffer_, that.buffer_);
}

#endif // EXTRAPOLATION_VECTOR_CPP