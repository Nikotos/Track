#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <iostream>

using namespace std;

/* -------------------------------------------------------
 *  Welcome on the tree!
 *
 *
 *
 /------------------------------------------------------*/

#include "acorn.h"



const int NODE_CANARY_LEFT = 13091984, NODE_CANARY_RIGHT = 80820128;

const char* TREE_LOG_FILE = "tree_log.txt";




enum LEX_TYPE
{
    OPERATOR_TYPE = 0,
    INT_CONSTANT,
    DOUBLE_CONSTANT,
    VARIABLE,
    END,
    LEX_TYPE_DEFAULT
};

/* arrray to convert enums numbers to strings*/
const char *LEX_TYPES_NAMES[] = {"OPERATOR_TYPE", "INT_CONSTANT", "DOUBLE_CONSTANT", "VARIABLE", "END",
                                 "LEX_TYPE_DEFAULT"};

enum OPERATOR_NAMES
{
    PLUS = 0,
    MINUS,
    MULTIPLY,
    DIVIDE,
    EQUAL,
    SIN,
    COS,
    OPERATOR_NAMES_DEFAULT
};


/* arrray to convert enums numbers to strings*/
const char *OP_NAMES[] = {"PLUS", "MINUS", "MULTIPLY", "DIVIDE", "EQUAL", "SIN", "COS", "OPERATOR_NAMES_DEFAULT"};



/* -------------------------------------------------------
 *  @about Lexical knot of our tree
 *         Storage and mode of its using
 *
 *         Heart of our Tree
 *
 /------------------------------------------------------*/
struct Lex_t
{
    /* mode of using our storage*/
    enum LEX_TYPE type_ = LEX_TYPE_DEFAULT;


    /* multi-mode storage*/
    union STORAGE
    {
        enum OPERATOR_NAMES oper_;
        double real_;
        int number_;

    };


    union STORAGE storage_;


    /*-----------------------------------------Functions---------------------------------------------*/

    explicit Lex_t(enum OPERATOR_NAMES);

    explicit Lex_t(double val);

    explicit Lex_t(int numb);

    /* to cactch errors and throw exceptions*/
    explicit Lex_t(...);

    ~Lex_t();

    inline Lex_t& operator = (const Lex_t& that);

    inline void print() const;
};



struct Node {

    Lex_t knot_;

    Node* left_node_ = nullptr;
    Node* right_node_ = nullptr;


    Node(){};


    /* "LT" - is Lexic type*/
    template <typename LT>
    Node(LT object);

    template <typename LT>
    void set_left(LT object);

    template <typename LT>
    void set_right(LT object);

    ~Node();

    Node& operator = (const Node& that);

    void surface_copy(const Node& that);

    inline void print() const;

};



struct Tree
{
    Node* root_ = nullptr;

    size_t size_ = 0;


    Tree(){};

    template <typename LT>
    Tree(LT object);

    ~Tree();

    inline void print() const;



};


#include "Tree.cpp"

#endif //TREE_H