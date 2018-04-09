#ifndef STACK_TEMPLATE_STACK_CPP
#define STACK_TEMPLATE_STACK_CPP

#include <assert.h>

#include "stack_t.h"

//-------------------------------------------------------------------------------------------
//! Special ASSERT for the Stack
//!
//! Make Dump, if something is wrong
//!
//-------------------------------------------------------------------------------------------
#define STACK_ASSERT(stack);    \
            if (!All_Correct()) \
            {                   \
                Dump();         \
                assert(0);      \
            }

//-------------------------------------------------------------------------------------------
//! Stack Checker
//!
//! Check all vital values
//!
//-------------------------------------------------------------------------------------------
template <typename data_T>
bool Stack_t<data_T>::All_Correct() const {
    int hash_val = Hash_val();
    int hash_body = Hash_body();

    return (this) && (count_st >= 1) && (body) && (count_st < size_st)
           && (canaryleft == Canary_1) && (canaryright == Canary_2)
           && (_hash_val == hash_val) && (_hash_body == hash_body)
           && (abs(body[0] - Body_canary_1) < Epsilon)
           && (abs(body[size_st - 1] - Body_canary_2) < Epsilon);
}

//-------------------------------------------------------------------------------------------
//! Hash function, which controls ("measures") VITAL values in the stack
//!
//! @note must be not commutative to avoid shuffling
//-------------------------------------------------------------------------------------------
template <typename data_T>
int Stack_t<data_T>::Hash_val() const {
    return  (canaryleft) * (int)(body) +
            (int)(body) * (count_st) +
            (count_st) * (size_st) +
            (size_st) * (canaryright);

}

//-------------------------------------------------------------------------------------------
//! Hash function which controls ("measures") all data in the stack
//!
//! @note must be not commutative to avoid shuffling
//-------------------------------------------------------------------------------------------
template <typename data_T>
int Stack_t<data_T>::Hash_body() const {
    int body_hash = 0;
    for (int i = 0; i < count_st - 1; i++){
        body_hash += (int) *(body + i) * (int) *(body + i + 1);
    }
    return body_hash;
}

//-------------------------------------------------------------------------------------------
//! Dump function for int values
//!
//! @param [in] value       int value
//! @param [in] dump_file   pointer on a file
//-------------------------------------------------------------------------------------------
template <typename data_T>
void Stack_t<data_T>::dump(const int value, FILE* dump_file) const{
    assert(dump_file != NULL);
    fprintf (dump_file, "%d\n", value);
}

//-------------------------------------------------------------------------------------------
//! Dump function for double values
//!
//! @param [in] value       double value
//! @param [in] dump_file   pointer on a file
//-------------------------------------------------------------------------------------------
template <typename data_T>
void Stack_t<data_T>::dump(const double value, FILE* dump_file) const {
    assert(dump_file != NULL);
    if (isnan (value))
        fprintf (dump_file, "// !! Not a Number !!\n");
    else
        fprintf (dump_file, "%9f\n", value);
}

//-------------------------------------------------------------------------------------------
//! Dump function for int pointers
//!
//! @param [in] value       pointer value
//! @param [in] dump_file   pointer on a file
//-------------------------------------------------------------------------------------------
template <typename data_T>
void Stack_t<data_T>::dump(const void* value, FILE* dump_file) const{
    assert(dump_file != NULL);
    data_T* val = (data_T *) value;

    if (val == NULL)
        fprintf (dump_file, "%p  - // !! NULL POINTER !!", val);
    else
        fprintf (dump_file, "%p\n", val);
}

//-------------------------------------------------------------------------------------------
//! Dump for all data + info about main protective tips
//!
//! @note dump_file  pointer on a file (output file for dump info)
//-------------------------------------------------------------------------------------------
template <typename data_T>
void Stack_t<data_T>::Dump() const {
    FILE* dump_file = fopen("dump.txt", "a");
    assert(dump_file != NULL);

    int hash_val = Hash_val();
    int hash_body = Hash_body();

    fprintf(dump_file, "{\n Stack_t ERROR!!! pointer is - [%p]\n", this);

    if (canaryleft != Canary_1) {
        fprintf(dump_file, "GAS!!! Poor LEFT CANARY has DIED! value is [%d] but expected [%d]\n", canaryleft, Canary_1);
    }
    else {
        fprintf(dump_file, "LEFT CANARY is OK, STILL ALIVE\n");
    }

    if (canaryright != Canary_2) {
        fprintf(dump_file, "GAS!!! Poor RIGHT CANARY has DIED! value is [%d] but expected [%d]\n", canaryright, Canary_2);
    }
    else {
        fprintf(dump_file, "RIGHT CANARY is OK, STILL ALIVE\n");
    }

    if (abs(body[0] - Body_canary_1) < Epsilon) {
        fprintf(dump_file, "GAS!!! Poor LEFT BODY CANARY has DIED! value is [%f] but expected [%f]\n", body[0], Body_canary_1);
    }
    else {
        fprintf(dump_file, "LEFT BODY CANARY is OK, STILL ALIVE\n");
    }

    if (abs(body[size_st - 1] - Body_canary_2) < Epsilon) {
        fprintf(dump_file, "GAS!!! Poor LEFT BODY CANARY has DIED! value is [%d] but expected [%d]\n", body[size_st - 1], Body_canary_2);
    }
    else {
        fprintf(dump_file, "LEFT BODY CANARY is OK, STILL ALIVE\n");
    }

    if (hash_val != _hash_val) {
        fprintf(dump_file,"ERROR!!! HASH of KEY values is WRONG!!! value is [%d], expected [%d]\n", hash_val, _hash_val);
    }
    else {
        fprintf(dump_file, "HASH of KEY values is OK\n");
    }

    if (hash_body != _hash_body) {
        fprintf(dump_file,"ERROR!!! HASH of DATA is WRONG!!! value is [%d], expected [%d]\n", hash_body, _hash_body);
    }
    else {
        fprintf(dump_file, "HASH of DATA is OK\n");
    }

    if (count_st <= 1) {
        fprintf(dump_file, "ERROR!!! (count_st = [%d] <= 1) !!!!\n", count_st);
    }
    else {
        fprintf(dump_file, "OK, (count_st = [%d])\n", count_st);
    }

    if (count_st + 2 >= size_st) {
        fprintf(dump_file, "ERROR!!! (count_st + 2 = [%d] >= size_st = [%d])\n", count_st + 2, size_st);
    }
    else {
        fprintf(dump_file, "OK, (count_st + 2 = [%d] < size_st = [%d])\n", count_st + 2, size_st);
    }

    if (size_st >= Min_stack_size) {
        fprintf(dump_file, "ERROR!!! (size_st = [%d] >= Min_stack_size = [%d]) !!!\n", size_st, Min_stack_size);
    }
    else {
        fprintf(dump_file, "OK, (size_st = [%d] <= Min_stack_size = [%d]) \n", size_st, Min_stack_size);
    }

    fprintf(dump_file, "Pointer at DATA is [%p]", body);

    for (int i = 0; i < count_st; i++)
    {
        fprintf (dump_file, " [%d] = ", i);
        dump (body[i], dump_file);
    }

    fprintf(dump_file,"\n}\n");

    fclose(dump_file);
}

//-------------------------------------------------------------------------------------------
//! Stack Constructor
//!
//! fill all vital values
//-------------------------------------------------------------------------------------------
template <typename data_T>
Stack_t<data_T>::Stack_t():

        canaryleft (Canary_1),
        canaryright(Canary_2),
        size_st (Min_stack_size + 2),
        count_st (1),
        body ({}),
        _hash_val (0),
        _hash_body (0)

{
    body = new data_T[size_st];
    body[0] = Body_canary_1;            // ! to think about
    body[size_st - 1] = Body_canary_2;  // !

    _hash_body = this->Hash_body();
    _hash_val = this->Hash_val();

    STACK_ASSERT(this);
}


//-------------------------------------------------------------------------------------------
//! Stack Constructor with size - parametr
//!
//! fill all vital values
//-------------------------------------------------------------------------------------------
template <typename data_T>
Stack_t<data_T>::Stack_t(size_t capacity):

        canaryleft (Canary_1),
        canaryright(Canary_2),
        size_st (capacity + 2),
        count_st (1),
        body ({}),
        _hash_val (0),
        _hash_body (0)

{
    body = new data_T[size_st];
    body[0] = Body_canary_1;            // ! to think about
    body[size_st - 1] = Body_canary_2;  // !

    _hash_body = this->Hash_body();
    _hash_val = this->Hash_val();

    STACK_ASSERT(this);
}

//-------------------------------------------------------------------------------------------
//! Stack Destructor
//!
//! @note clear and fill parametrs with start values
//-------------------------------------------------------------------------------------------
template <typename data_T>
Stack_t <data_T>::~Stack_t(){
    STACK_ASSERT(this);
    for (int i = 0; i < size_st; i++) {
        body[i] = Body_poison;
    }
    if (body != (data_T*) Start_pointer) {
        free(body);
        body = (data_T*) Start_pointer;
    }
}

//-------------------------------------------------------------------------------------------
//! Put the value at the end of the stack
//!
//! @param [in] value       value to been put
//!
//! @note double the size of the stack if it's needed (using "Double_size()")
//-------------------------------------------------------------------------------------------
template <typename data_T>
void Stack_t<data_T>::Push(data_T value) {
    STACK_ASSERT(this);

    if (count_st + 1 == size_st) {
        Double_size();
        body[count_st] = value;
        count_st++;

        _hash_body = Hash_body();
        _hash_val = Hash_val();
        STACK_ASSERT(this);
    }
    else {
        body[count_st] = value;
        count_st++;

        _hash_body = Hash_body();
        _hash_val = Hash_val();
        STACK_ASSERT(this);
    }
}

//-------------------------------------------------------------------------------------------
//! Increasing the size of the stack
//!
//! Double the stack's size
//-------------------------------------------------------------------------------------------
template <typename data_T>
void Stack_t<data_T>::Double_size() {
    STACK_ASSERT(this);
    body[size_st - 1] = 0;

    body = (data_T*)realloc(body, 2*(size_st)*sizeof(data_T));  // ?? can we use realloc here&
    size_st *= 2;
    body[size_st - 1] = Body_canary_2;

    _hash_val = Hash_val();
    _hash_body = Hash_body();

    STACK_ASSERT(this);

}
//-------------------------------------------------------------------------------------------
//! Take the value from the top of stack
//!
//! @return the value of Stack's top element
//!
//! @note also delete this element from stack
//-------------------------------------------------------------------------------------------
template <typename data_T>
data_T Stack_t<data_T>::Pop() {
    STACK_ASSERT(this);
    count_st--;

    _hash_val = Hash_val();
    _hash_body = Hash_body();

    STACK_ASSERT(this);
    return body[count_st];

}

//-------------------------------------------------------------------------------------------
//! Just get the value from the top of stack
//!
//! @return the value of Stack's top element
//!
//! @note just get this element from stack
//-------------------------------------------------------------------------------------------
template <typename data_T>
data_T Stack_t<data_T>::Get() const{
    STACK_ASSERT(this);
    return body[count_st - 1];
}

//-------------------------------------------------------------------------------------------
//! Gives number of elements in stack
//!
//! @return number of elements in stack
//!
//-------------------------------------------------------------------------------------------
template <typename data_T>
int Stack_t<data_T>::Size() const {
    STACK_ASSERT(this);
    return count_st;
}

//-------------------------------------------------------------------------------------------
//! Check if stack is empty
//!
//! @return 1 if EMPTY
//! @return 0 if NOT EMPTY
//-------------------------------------------------------------------------------------------
template <typename data_T>
bool Stack_t<data_T>::Empty() const {
    STACK_ASSERT(this);
    return (count_st == 1);
}
#endif //STACK_TEMPLATE_STACK_CPP
