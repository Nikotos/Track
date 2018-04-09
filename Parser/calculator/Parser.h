#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <iostream>


#include "acorn.h"
using namespace std;

/* -------------------------------------------------------
 *  class Parser
 *
 *
 *
 /------------------------------------------------------*/
class Parser
{
private:
    const char* string_ = nullptr;
    int pos_ = -1;
public:
    Parser(){};

    Parser(const char* string):
        string_(string),
        pos_ (0)
        {}

    int Pars();

    int GetE();

    int GetT();

    int GetP();

    int GetN();

};


#include "Parser.cpp"

#endif //PARSER_H