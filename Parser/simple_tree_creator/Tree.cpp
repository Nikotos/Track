#ifndef TREE_CPP
#define TREE_CPP

#include "Tree.h"








/* =================================================================================================
 *
 *                                  Lex_t struct, Implementation
 *
 *
 *
 /==================================================================================================*/



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
    type_ = LEX_TYPE_DEFAULT;
    storage_.real_ = NAN;
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
        THROW(LOGIC_ERROR, "Node if alredy exist!", nullptr);
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
        delete left_node_;
        delete right_node_;

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

/* =================================================================================================
 *
 *                                  Tree class, Implementation
 *
 *
 *
 /==================================================================================================*/

/* -------------------------------------------------------
 *  @about
 *          Tree Constructor
 *          without parameters
 *
 /------------------------------------------------------*/
template  <typename LT>
Tree::Tree(LT object)
{
    root_ = new Node(object);
};


/* -------------------------------------------------------
 *  @about
 *          Tree Destructor
 *
 *
 /------------------------------------------------------*/
Tree::~Tree()
{
    /* destructors for Nodes will be called because of "delete" */
    delete root_;
    size_ = 0;
};

inline void Tree::print() const
{
    root_->print();
}

#endif //TREE_CPP