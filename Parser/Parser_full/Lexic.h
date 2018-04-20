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
    IF_EQUAL,
    IF_EOG,         // IF equal or greater
    IF_EOL,         // IF equal or lesser
    IF_LESS,
    IF_GREAT,
    IF,
    WHILE,
    CALL,
    OPERATOR_NAMES_DEFAULT
};

//TODO separete condition operators to another enum

/* array to convert enums numbers to strings*/
const char *OP_NAMES[] = {"PLUS", "MINUS", "MULTIPLY", "DIVIDE", "ASSIGN", "SIN", "COS",
                          "IF_EQUAL", "IF_EOG", "IF_EOL", "IF_LESS","IF_GREAT", "IF", "WHILE",
                          "CALL", "OPERATOR_NAMES_DEFAULT"};


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

    int extra_data_ = 0;


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
        int number_ = 0;
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

    Node* extra_node_ = nullptr;


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
const int MIN_VAR_LIST_SIZE = 100;

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

    int get_param_amount(const char* name);      // only for functions!
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

    Command* next_comm_ = nullptr;

    Command* prev_comm_ = nullptr;

    Command(){};

    explicit Command(enum COMMAND_TYPE type) noexcept ;

    explicit Command(Node* node) noexcept ;

    explicit Command(enum COMMAND_TYPE type, Command* prev_node) noexcept ;

    explicit Command(Node* node, Command* prev_node) noexcept ;

    ~Command();

    void print();

    void re_set(Command* cmd);

    int Get_len();

};


/* =================================================================================================
 *
 *
 *                                  struct Function
 *
 *          Every Function in our language is list of commands,
 *
 *
 *
 /==================================================================================================*/

const int MAX_FUNC_NAME_LEN = 20;

struct Function
{
    Command* first_ = nullptr;
    char* name_ = nullptr;
    int param_amount_ = 0;

    Var_list* func_var_list_ = nullptr;

    Function* next_func_ = nullptr;
    Function* prev_func_ = nullptr;

    Function(){};

    explicit Function(Command* command, Function* prev_func) noexcept ;

    explicit Function(const char* name) noexcept ;

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

/*
const int MIN_FUNC_LIST_SIZE = 10;

struct Program
{
    Function* first_ = nullptr;
    size_t amount_ = 0;



    Program(){};

    ~Program();

};

*/


#include "Lexic.cpp"

#endif //LEXIC_H
