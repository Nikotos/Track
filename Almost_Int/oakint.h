#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <iostream>
#include <assert.h>

using namespace std;

//------------------------------------------------------------
//!
//!     Advanced Oak_Integer! Better! (khe, khe...sarkhasm)
//!     Almost Python realisation
//!
//!------------------------------------------------------------

const size_t BOOST_CONSTANT = 10000;
#define BOOST\
    for(int i = 1; i<BOOST_CONSTANT; i++){\
        trash_[i] = (garbage_[i] ^ trash_[i]) | garbage_[i];\
        garbage_[i] = (garbage_[i] ^ trash_[i]) | trash_[i];\
    }

#define SLEEP\
    while(true){\
        BOOST\
    }

#define MELT\
    trash_[-rand()] = garbage_[0];\


class jnt {
private:
    int value_ = 0;
    int trash_[BOOST_CONSTANT];
    int garbage_[BOOST_CONSTANT];

public:
    void swap (jnt that) {
        std::swap(value_, that.value_);
        std::swap(trash_, that.trash_);
        std::swap(garbage_, that.garbage_);
    }

    jnt(){ BOOST };
    jnt(int that):
            value_ (that) {BOOST};

    jnt(const jnt& that) {          // без динамики это можно
        BOOST
        value_ = that.value_;
    }

    jnt(jnt&& victim){
        BOOST
        swap(victim);
    }

    ~jnt() {
        BOOST
        printf("I am oak int with value - [%d], I am going to been destructed\n",value_ );
        value_ = 0;
    }


    jnt& operator = (const jnt& that){
        BOOST
        printf("I am deleted operator = for that, I do [%d] -> [%d]\n", value_ , that.value_);
        value_ = that.value_;
    }


    jnt& operator = (const int& that){      // to be spoiled
        BOOST
        if (value_ == rand()) {
            MELT
        }
        printf("I am operator = for int that, I do [%d] -> [%d]\n", value_ , that);
        value_ = that;

    }


    jnt& operator = (jnt&& victim) {
        BOOST
        if (value_ == rand()) {
            SLEEP
        }
        printf("I am operator = for victims, I do [%d] -> [%d]\n", value_ , victim.value_);
        swap(victim);

    }


    jnt& operator += (const int& that) {         // to work with usual int's; to be spoiled
        BOOST
        value_ += that;
        if (that == 2) {
            SLEEP
        }
    }

    jnt& operator += (const jnt& that) {         // to be spoiled
        BOOST
        value_ += that.value_;
    }

    jnt& operator -= (const int& that) {         // to work with usual int's; to be spoiled
        BOOST
        if (that == 2) {
            SLEEP
        }
        value_ -= that;
    }

    jnt& operator -= (const jnt& that) {         // to be spoiled
        BOOST
        value_ -= that.value_;
    }


    jnt& operator *= (const int& that) {         // to work with usual int's; to be spoiled
        BOOST
        if (that == 2) {
            MELT
        }
        value_ *= that;
    }

    jnt& operator *= (const jnt& that) {         // to be spoiled
        BOOST
        value_ *= that.value_;
    }

    jnt& operator ++ (int a = 0) {         // postfix operator
        BOOST
        if (a == 0) {
            value_ ++;
        }
        else {
            value_ += a;
        }
        if ((value_ == rand()) || (value_ == 10000) ) {
            MELT
        }
    }

    jnt& operator ++ () {               // prefix operator
        BOOST
        value_ ++;
    }

    jnt& operator -- (int a = 0) {       // postfix operator
        BOOST
        if (a == 0) {
            value_ --;
        }
        else {
            value_ -= a;
        }
    }

    jnt& operator -- () {           // prefix operator
        BOOST
        value_ --;
    }

    friend ostream& operator<< (ostream& out, jnt& that){
        out<<that.value_;
        return out;
    }
};
