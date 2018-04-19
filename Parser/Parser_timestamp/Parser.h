#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <cstring>

/*=========================================================================================================
 *
 *
 *                                          Parser
 *
 *
 *
 /==========================================================================================================*/

#include "acorn.h"
#include "Lexic.h"

using namespace std;


/* ---------------------------------------------------------------------------------
 *
 *          my struct string
 *          for some operations
 *
 *
 /-------------------------------------------------------------------------------------*/
namespace oak
{

    struct string
    {
        char* body_ = nullptr;
        int len_ = 0;
    };
}


/* ---------------------------------------------------------------------------------
 *
 *          struct Parser
 *
 *
 /-------------------------------------------------------------------------------------*/
struct Parser
{

    const char* string_ = nullptr;
    int pos_ = -1;

    /* heap to put symbols from file*/
    char* heap_ = nullptr;


    /* array of strings from input file*/
    oak::string* text_ = nullptr;
    int strings_amount_ = 0;

    /* Variables list, to "catch" undefined variables*/
    Var_list* var_list_;



    /*-----------------------------Functions-----------------------------*/

    Parser();

    Parser(const char* string);

    ~Parser();

    void Read_file(const char* filename);

    size_t sizeof_file(FILE* file);

    size_t str_amount(const char* heap);

    void split_text();

    //void Get_programm(Program* functions);

    void Get_function(Function* func);

    Command* Get_command();

    void SetVar(enum VAR_TYPES type);

    Node* GetA(); // Get Assignment Operation

    Node* GetE(); // Get Expression

    Node* GetT(); // Get * or / expression

    Node* GetP(); //  Get expression in brackets

    Node* GetN(); // Get Number

    Node* GetV(); // Get Variable

};



#include "Parser.cpp"

#endif //PARSER_H