#ifndef LEXIC_H
#define LEXIC_H

#include <iostream>
#include <cstring>

#include "acorn.h"

using namespace std;

/* =================================================================================================
 *
 *                                  Some Lexical basics of the language
 *
 *
 *
 /==================================================================================================*/


enum LEX_TYPE
{
    OPERATOR_TYPE = 0,
    INT_CONSTANT,
    DOUBLE_CONSTANT,
    VARIABLE,
    CONDITION,
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
    ASSIGN,
    SIN,
    COS,
    OPERATOR_NAMES_DEFAULT
};


/* array to convert enums numbers to strings*/
const char *OP_NAMES[] = {"PLUS", "MINUS", "MULTIPLY", "DIVIDE", "ASSIGN", "SIN", "COS", "OPERATOR_NAMES_DEFAULT"};


enum VAR_TYPES
{
    INTEGER = 0,
    DOUBLE,
    VAR_TYPES_DEFAULT
};

const int MAX_VAR_NAME_LEN = 32;

enum COMMAND_TYPE
{
    VARIABLE_DEFINITION = 0,
    TREE,
    COMMAND_TYPE_DEFAULT
};

/* =================================================================================================
 *
 *                                 class Variable, Header
 *
 *        Variable with some functions
 *        some useful functions
 *
 *
 *
 /==================================================================================================*/
struct Variable
{
    enum VAR_TYPES type_ = VAR_TYPES_DEFAULT;
    char* name_ = nullptr;
    int id_ = -1;



    Variable(){};

    Variable(enum VAR_TYPES type, const char* name, int id);

    Variable(const Variable& that);

    ~Variable();

    Variable& operator = (Variable that) noexcept ;

    void swap(Variable& that) noexcept;
};


/* =================================================================================================
 *
 *                                  Lex_t struct, Header
 *
 *        Lexical knot of our tree
 *        Storage and mode of its using
 *        Heart of our Tree
 *
 *
 /==================================================================================================*/
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
        Variable* var_;

    };


    union STORAGE storage_;


    /*-----------------------------------------Functions---------------------------------------------*/

    explicit Lex_t(enum OPERATOR_NAMES);

    explicit Lex_t(double val);

    explicit Lex_t(int numb);

    explicit Lex_t(Variable* var);

    /* to cactch errors and throw exceptions*/
    explicit Lex_t(...);

    ~Lex_t();

    inline Lex_t& operator = (const Lex_t& that);

    inline void print() const;
};


/* =================================================================================================
 *
 *                                  Welcome on the Tree!
 *
 *
 *
 *
 *
 /==================================================================================================*/




/* =================================================================================================
 *
 *                                  struct Node
 *
 *
 *
 /==================================================================================================*/
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




/* =================================================================================================
 *
 *                                  class Variables List
 *
 *
 *
 *
 /==================================================================================================*/
const int MIN_VAR_LIST_SIZE = 10;

struct Var_list
{

    Variable* list_ = nullptr;

    size_t amount_ = 0;

    /* to collect symbols to names while Parsing */
    char* name_buffer_ = nullptr;




    Var_list(){};

    explicit Var_list(size_t capacity);

    ~Var_list();

    inline bool is_in(const char* name) const;

    Variable* get_var(const char* name) const;

    void add_variable(enum VAR_TYPES type, const char* name);

    void clean_name_buffer();

    void swap(Var_list& that);

    //void del_variable(const char* name);
};


/* =================================================================================================
 *
 *                                  struct Command
 *
 *          Every Function in our language is list of commands,
 *          and every Command is a Tree
 *
 *
 /==================================================================================================*/
struct Command
{
    enum COMMAND_TYPE type_ = COMMAND_TYPE_DEFAULT;
    Node* root_ = nullptr;

    Command(){};

    explicit Command(enum COMMAND_TYPE type) noexcept ;

    explicit Command(Node* node) noexcept ;

    ~Command();

    void print();

    void re_set(Command* cmd);

};


/* =================================================================================================
 *
 *                                  struct Function
 *
 *          Every Function in our language is list of commands,
 *
 *
 *
 /==================================================================================================*/
const int MIN_FUNCTION_SIZE = 10;

struct Function
{
    Command* list_ = nullptr;
    int size_ = 0;
    int amount_ = 0;

    Function(){};

    explicit Function(size_t capacity);

    ~Function();

    void print();
};

/* =================================================================================================
 *
 *                                  struct Program
 *
 *          Every Program in our language is list of Functions,
 *          and every Function is a list of Commands
 *          and every Command is a Tree
 *
 /==================================================================================================*/
const int MIN_FUNC_LIST_SIZE = 10;

struct Program
{
    Function* list_ = nullptr;
    size_t amount_ = 0;

    Program(){};

    explicit Program(size_t capacity);

    ~Program();

};




#include "Lexic.cpp"

#endif //LEXIC_H
