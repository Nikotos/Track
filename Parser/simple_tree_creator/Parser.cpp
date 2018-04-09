#ifndef PARSER_CPP
#define PARSER_CPP

#include "Parser.h"


/* -------------------------------------------------------
 * @about
 *        Functions for Parser
 *
 *
 *
 /------------------------------------------------------*/




#define SPACE_CORRECTION\
    while (string_[pos_] == ' ')\
    {\
        pos_++;\
    }

/* -------------------------------------------------------
 * @about
 *        Get Number, usual worker
 *
 /--------------------------------------------------------*/
#define IS_DIGIT\
    ((string_[pos_] >= '0') && (string_[pos_] <= '9'))

Node* Parser::GetN()
{
    SPACE_CORRECTION

    if (!IS_DIGIT){
        THROW(SYNTAX_ERROR ,"Syntax error! Isn't a number!", nullptr);
    }

    int val = 0;

    /* Probably more, that one roundabout, because of checking above*/
    while (IS_DIGIT)
    {
        val = 10 * val + (string_[pos_] - '0');
        pos_ ++;
    }

    if (string_[pos_] == '.')
    {
        pos_++;

        double real = 0;
        double multiplier = 0.1;

        while (IS_DIGIT)
        {
            real += multiplier * (string_[pos_] - '0');
            pos_ ++;
            multiplier /= 10;
        }

        real += val;

        SPACE_CORRECTION

        return new Node(real);
    }

    else
    {
        SPACE_CORRECTION

        return new Node(val);
    }

}
#undef IS_DIGIT


/* -------------------------------------------------------
 * @about
 *        Modified 'Get Number', secret agent
 *        Makes 'trash', when notices bracket
 *        (To be honest Calculating expression in brackets)
 *        
 *
 /--------------------------------------------------------*/
#define CHECK_CLOSING_BRACKET\
    if (string_[pos_] == ')')\
    {\
        pos_ ++;\
    }\
\
    else\
    {\
        THROW(SYNTAX_ERROR, "Alone standing [ ( - bracket]", nullptr);\
    }


Node* Parser::GetP()
{
    SPACE_CORRECTION

    if(string_[pos_] == '(')
    {
        pos_ ++;

        Node* current_node;
        current_node = GetE();


        CHECK_CLOSING_BRACKET

        SPACE_CORRECTION

        return current_node;
    }
    else if (strncmp(string_ + pos_, "sin(", 4) == 0)
    {
        pos_ += 4;    // "SIN(Expression)" - 4 sym before Expression

        Node* current_node = new Node(SIN);
        current_node->left_node_ = GetE();
        current_node->right_node_ = nullptr;    //explicit form to write unary operator


        CHECK_CLOSING_BRACKET

        SPACE_CORRECTION

        return current_node;
    }
    else if (strncmp(string_ + pos_, "cos(", 4) == 0)
    {
        pos_ += 4;    // "COS(Expression)" - 4 sym before Expression

        Node* current_node = new Node(COS);
        current_node->left_node_ = GetE();
        current_node->right_node_ = nullptr;    //explicit form to write unary operator



        CHECK_CLOSING_BRACKET

        SPACE_CORRECTION

        return current_node;
    }
    else 
    {
        return GetN();
    }
}


/* -------------------------------------------------------
 * @about
 *        one more 'Get Expression', Maestro of '*' and '/'
 *        Petty officer in our project
 *        Calculating expressions (* or /)
 *
 *
 /--------------------------------------------------------*/
Node* Parser::GetT()
{

    Node* current_node = new Node(OPERATOR_NAMES_DEFAULT);
    current_node->left_node_ = GetP();

    int counter = 0;

    while ((string_[pos_] == '*') || (string_[pos_] == '/'))
    {
        if (counter > 0)
        {
            Node* second_node = new Node(OPERATOR_NAMES_DEFAULT);
            second_node->left_node_ = current_node;

            current_node = second_node;
        }


        if (string_[pos_] == '*')
        {
            current_node->knot_.storage_.oper_ = MULTIPLY;
        }

        else
        {
            current_node->knot_.storage_.oper_ = DIVIDE;
        }

        pos_++;

        current_node->right_node_  = GetP();

        counter++;

    }

    if (counter == 0)
    {
        return current_node->left_node_;
    }
    else
    {
        return current_node;
    }

}

/* -------------------------------------------------------
 * @about
 *        'Get Expression', Maestro of '+' and '-'
 *        Foreman in our project
 *        Calculating expressions (+ or -)
 *
 *
 /--------------------------------------------------------*/
Node* Parser::GetE()
{

    Node* current_node = new Node(OPERATOR_NAMES_DEFAULT);
    current_node->left_node_ = GetT();

    int counter = 0;

    while ((string_[pos_] == '+') || (string_[pos_] == '-'))
    {
        if (counter > 0)
        {
            Node* second_node = new Node(OPERATOR_NAMES_DEFAULT);
            second_node->left_node_ = current_node;

            current_node = second_node;
        }


        if (string_[pos_] == '+')
        {
            current_node->knot_.storage_.oper_ = PLUS;
        }
        else
        {
            current_node->knot_.storage_.oper_ = MINUS;
        }

        pos_++;

        current_node->right_node_  = GetT();

        counter++;

    }

    if (counter == 0)
    {
        return current_node->left_node_;
    }
    else
    {
        return current_node;
    }

}


/* -------------------------------------------------------
 * @about
 *        Fills parsing tree
 *
 * @input
 *        pointer at empty tree
 *
 * @output
 *         Parser tree
 *         (almost output, we work with a pointer)
 *
 /--------------------------------------------------------*/
void Parser::Get_pars_tree(Tree *tree)
{
    SPACE_CORRECTION

    tree->root_ = GetE();

    if (string_[pos_] != 0)
    {
        printf("Incorrect symbol! [%s]\n", string_ + pos_);
        THROW(SYNTAX_ERROR, "Incorrect symbol!", nullptr);
    }
    else
    {

    }
}




#endif //PARSER_CPP