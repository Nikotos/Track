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
#include "Tree.h"

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

    void Get_pars_tree(Tree* tree);

    Node* GetE();

    Node* GetT();

    Node* GetP();

    Node* GetN();

};


#include "Parser.cpp"

#endif //PARSER_H