#ifndef LEXIC_CPP
#define LEXIC_CPP



/* =================================================================================================
 *
 *                                  Lex_t struct, Implementation
 *
 *
 *
 /==================================================================================================*/
#include "Lexic.h"


/* -------------------------------------------------------
 *  @about
 *          Constructor for operators
 *
 /------------------------------------------------------*/
Lex_t::Lex_t(enum OPERATOR_NAMES oper):
        type_ (OPERATOR_TYPE)
{
    storage_.oper_ = oper;
}



/* -------------------------------------------------------
 *  @about
 *          Constructor for double data
 *
 /------------------------------------------------------*/
Lex_t::Lex_t(double val):
        type_(DOUBLE_CONSTANT)
{
    storage_.real_ = val;
}


/* -------------------------------------------------------
 *  @about
 *          Constructor for Integer data
 *
 /------------------------------------------------------*/
Lex_t::Lex_t(int numb):
        type_(INT_CONSTANT)
{
    storage_.number_ = numb;
}

/* -------------------------------------------------------
 *  @about
 *          Constructor for Variables
 *
 /------------------------------------------------------*/
Lex_t::Lex_t(Variable* var):
        type_(VARIABLE)
{
    storage_.var_ = var ;
}

/* -----------------------------------------------------------------------------------
 *  @about
 *          Special overload with aim to Throw exception, if type is unknown
 *
 *
 *
 /---------------------------------------------------------------------------------*/
Lex_t::Lex_t(...)
{
    THROW(LOGIC_ERROR, "This type of input is inappropriate!", nullptr);
}


/* --------------------------------------------------------------------
 *  @about
 *         Lex_t destructor
 *
 *
 /---------------------------------------------------------------------*/
Lex_t::~Lex_t()
{
    if (this!= nullptr)
    {
        type_ = LEX_TYPE_DEFAULT;
        storage_.real_ = 0;
    }
}


/* --------------------------------------------------------------------
 *  @about
 *         operator =
 *
 *
 /---------------------------------------------------------------------*/
inline Lex_t& Lex_t::operator=(const Lex_t& that)
{
    type_ = that.type_;
    storage_ = that.storage_;
}


inline void Lex_t::print() const
{
    switch(type_)
    {
        case OPERATOR_TYPE:
        {
            printf("operator type is - [%s], data - [%s]\n", "OPERATOR", OP_NAMES[storage_.oper_]);
        }
            break;

        case INT_CONSTANT:
        {
            printf("operator type is - [%s], data - [%d]\n", "INT_CONSTANT", storage_.number_);
        }
            break;

        case DOUBLE_CONSTANT:
        {
            printf("operator type is - [%s], data - [%f]\n", "DOUBLE_CONSTANT", storage_.real_);
        }
            break;

        case VARIABLE:
        {
            printf("operator type is - [%s], data - [%s]\n", "VARIABLE", storage_.var_->name_);
        }
            break;

    }

}



/* =================================================================================================
 *
 *                                  Node struct, Implementation
 *
 *
 *
 /==================================================================================================*/


/* -------------------------------------------------------
 *  @about
 *      Template  Node constructor
 *
 *
 *      Template, because we have several types
 *
 /------------------------------------------------------*/
template <typename LT>
Node::Node(LT object):
        knot_(Lex_t(object)),
        left_node_(nullptr),
        right_node_(nullptr)
{};



/* -------------------------------------------------------
 *  @about
 *      Adding left node
 *
 *
 *      Template, because we have several types
 *
 /------------------------------------------------------*/
template <typename LT>
void Node::set_left(LT object)
{
    if (left_node_ != nullptr)
    {
        THROW(LOGIC_ERROR, "Node if already exist!", nullptr);
    }

    else
    {
        left_node_ = new Node(object);
    }
}


/* -------------------------------------------------------
 *  @about
 *      Adding right node
 *
 *
 *      Template, because we have several types
 *
 /------------------------------------------------------*/
template <typename LT>
void Node::set_right(LT object)
{
    if (right_node_ != nullptr)
    {
        THROW(LOGIC_ERROR, "Node if alredy exist!", nullptr);
    }

    else
    {
        right_node_ = new Node(object);
    }
}


/* -------------------------------------------------------
 *  @about
 *        Tree destructor
 *
 *
 *      Destructs node and all its sub-nodes
 *
 /------------------------------------------------------*/
Node::~Node()
{

    if (this != nullptr)
    {
        delete right_node_;
        delete left_node_;

        left_node_ = nullptr;
        right_node_ = nullptr;
    }
};


/* --------------------------------------------------------------------------------------
 *  @about
 *      operator = is NOT Implemented!
 *
 *
 *      Just "catches" errors and throws exceptions
 *
 /-------------------------------------------------------------------------------------*/
Node& Node::operator = (const Node& that)
{
    THROW(LOGIC_ERROR,"Sorry operator= for Node is deleted because of safety", nullptr);
}



void Node::surface_copy(const Node &that)
{
    knot_ = that.knot_;
    left_node_ = that.left_node_;
    right_node_ = that.right_node_;
}

inline void Node::print() const
{
    if (this != nullptr)
    {
        left_node_->print();

        right_node_->print();
        knot_.print();

    }
}

/*===========================================================================================================
 *
 *
 *                                       Variable functions
 *
 *
 *
 /==========================================================================================================*/

/* -------------------------------------------------------------------
 * @about
 *        Constructor for variable
 *
 /--------------------------------------------------------------------*/
Variable::Variable(enum VAR_TYPES type, const char *name, int id)
{
    type_ = type;
    id_ = id;

    size_t len = strlen(name);

    if (len > MAX_VAR_NAME_LEN)
    {
        THROW(SYNTAX_ERROR, "Variable name is too big!", nullptr);
    }
    else
    {
        name_ = new char [len];
        strcpy(name_, name);
    }
}


/* -------------------------------------------------------------------
 * @about
 *        Copy constructor for variable
 *
 /--------------------------------------------------------------------*/
Variable::Variable(const Variable& that)
{

    name_ = new char [sizeof(that.name_)];

    strcpy(name_, that.name_);

    type_ = that.type_;
    id_ = that.id_;

}


/* -------------------------------------------------------------------
 * @about
 *        Destructor for variable
 *
 /--------------------------------------------------------------------*/
Variable::~Variable()
{

    type_ = VAR_TYPES_DEFAULT;

    id_ = -1;


    delete [] name_;
    name_ = nullptr;

}


/* -------------------------------------------------------------------
 * @about
 *        Operator =  for Variable
 *        for long-lived objects
 *
 /--------------------------------------------------------------------*/
Variable& Variable::operator= (Variable that) noexcept
{
    swap(that);
}




/* -------------------------------------------------------------------
 * @about
 *        swap procedure for variable
 *
 /--------------------------------------------------------------------*/
void Variable::swap(Variable& that) noexcept
{
    std::swap(type_, that.type_);
    std::swap(name_, that.name_);
    std::swap(id_, that.id_);
}



/*===========================================================================================================
 *
 *
 *                                       Variables List functions
 *
 *
 *
 /==========================================================================================================*/
/* -------------------------------------------------------
 * @about
 *        Constructor for variables list
 *
 /--------------------------------------------------------*/
Var_list::Var_list(size_t capacity)
{
    if (capacity <= MIN_VAR_LIST_SIZE)
    {
        list_ = new Variable [MIN_VAR_LIST_SIZE];
    }
    else
    {
        list_ = new Variable [capacity];
    }


    name_buffer_ = new char [MAX_VAR_NAME_LEN];

    amount_ = 0;
}


/* -------------------------------------------------------
 * @about
 *        Check if variable is already in list
 *
 * @input
 *        Variable name
 *
 * @output
 *         true or false
 *
 /--------------------------------------------------------*/
inline bool Var_list::is_in(const char *name) const
{
    bool yeah_it_is = false;

    for(int i = 0; i < amount_; i++)
    {
        if(strcmp(list_[i].name_, name) == 0)
        {
            yeah_it_is = true;
        }
    }

    return yeah_it_is;
}


/* -------------------------------------------------------------------
 * @about
 *        returns Variable from Variables list
 *
 *
 /--------------------------------------------------------------------*/
Variable* Var_list::get_var(const char* name) const
{
    if (!is_in(name))
    {
        THROW(SYNTAX_ERROR, "Unknown variable!", nullptr);
    }
    else
    {
        for(int i = 0; i < amount_; i++)
        {
            if(strcmp(list_[i].name_, name) == 0)
            {
                return &list_[i];
            }
        }
    }

}


/* -------------------------------------------------------
 * @about
 *       Adds variable to list
 *       Throws if variable is already in list
 *
 /--------------------------------------------------------*/
void Var_list::add_variable(enum VAR_TYPES type, const char *name)
{
    if (is_in(name))
    {
        THROW(SYNTAX_ERROR, "Duplicate declaration of variable!", nullptr);
    }
    else
    {
        list_[amount_] = Variable(type, name, amount_);
        amount_++;
    }

}


/* -------------------------------------------------------
 * @about
 *       Destructor for Variables list
 *
 /--------------------------------------------------------*/
Var_list::~Var_list()
{
    amount_ = 0;


    if (name_buffer_ != nullptr)
    {
        delete [] name_buffer_;
    }

    if (list_ != nullptr)
    {
        delete [] list_;
        list_ = nullptr;
    }

}




void Var_list::clean_name_buffer()
{
    for(int i = 0; i < MAX_VAR_NAME_LEN; i++)
    {
        name_buffer_[i] = 0;
    }
}


void Var_list::swap(Var_list& that)
{
    std::swap(list_, that.list_);
    std::swap(amount_, that.amount_);
    std::swap(name_buffer_, that.name_buffer_);
}
/* =================================================================================================
 *
 *                                  struct Command, Implemantation
 *
 *
 * 
 *
 /==================================================================================================*/
Command::Command(enum COMMAND_TYPE type) noexcept
{
    root_ = nullptr;
    type_ = type;
}

Command::Command(Node* node) noexcept
{
    root_ = node;
    type_ = TREE;
}

Command::~Command()
{
    if(root_ != nullptr)
    {
        delete root_;
        root_ = nullptr;
    }

}

void Command::print()
{
    if (type_ == TREE)
    {
        root_->print();
        printf("\n");
    }

}



/* -------------------------------------------------------
 * @about
 *       Almost stealing constructor
 *
 /--------------------------------------------------------*/
void Command::re_set(Command *cmd)
{
    root_ = cmd->root_;
    cmd->root_ = nullptr;

    type_ = cmd->type_;
    cmd->type_ = COMMAND_TYPE_DEFAULT;
}


/* =================================================================================================
 *
 *                                  Commands List struct, Implementation
 *
 *
 *
 /==================================================================================================*/

Function::Function(size_t capacity)
{
    //printf("Function Created, size - [%d]", capacity);
    list_ = new Command[capacity];
    size_ = capacity;
    amount_ = 0;
}


Function::~Function()
{
    if (size_ != 0)
    {
        delete [] list_;
        list_ = nullptr;
        size_= 0;
        amount_ = 0;
    }
}


void Function::print()
{
    for(int i = 0; i < amount_; i++)
    {
        list_[i].print();
    }
}

/* =================================================================================================
 *
 *                                  struct Functions List
 *
 *
 *
 /==================================================================================================*/
Program::Program(size_t capacity)
{
    list_ = new Function[capacity];
}


Program::~Program()
{
    if(list_ != nullptr)
    {
        delete [] list_;
        list_ = nullptr;
    }
}


#endif //LEXIC_CPP