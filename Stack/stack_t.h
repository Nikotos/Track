    ///STACK
#ifndef STACK_TEMPLATE_STACK_H
#define STACK_TEMPLATE_STACK_H

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <iostream>
#include <assert.h>



const int Min_stack_size = 10;
const int Canary_1 = 1234567, Canary_2 = 7654321;
const int Body_canary_1 = 1234569, Body_canary_2 = 9654321;;
const int Start_pointer = 11;
const int Body_poison = 112233;
const double Epsilon = 0.000001;

template <typename data_T >
struct Stack_t {

    private:
        int canaryleft;

        data_T* body;

        int count_st;       // last index
        int size_st;        // the size of stack
        int _hash_val;
        int _hash_body;

        int canaryright;

        int Hash_val() const;
        int Hash_body() const;
        void dump(int value, FILE* dump_file) const;
        void dump(double value, FILE* dump_file) const;
        void dump(const void* value, FILE* dump_file) const;
        void Double_size();

    public:
        Stack_t();
        Stack_t(size_t capacity);
        ~Stack_t();
        bool All_Correct() const;
        void Push(data_T value);
        data_T Pop();
        data_T Get() const;
        int Size() const;        // number of elements in stack
        bool Empty() const;
        void Dump() const;
};

#include "stack.cpp"

#endif //STACK_TEMPLATE_STACK_H