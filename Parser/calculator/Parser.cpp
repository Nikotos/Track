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


#define THROW(ERRCODE, MESSAGE, POINTER)\
    throw new Acorn(ERRCODE, MESSAGE , __PRETTY_FUNCTION__,__FILE__,__LINE__, POINTER)


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

int Parser::GetN()
{
    SPACE_CORRECTION

    if (!IS_DIGIT){
        THROW(SYNTAX_ERROR ,"Syntax error! Isn't a number!", nullptr);
    }

    int val = 0;

    /* Probably more, that one roundabout*/
    while (IS_DIGIT)
    {
        val = 10 * val + (string_[pos_] - '0');
        pos_ ++;
    }

    SPACE_CORRECTION

    return val;
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
int Parser::GetP()
{
    SPACE_CORRECTION

    if(string_[pos_] == '(')
    {
        pos_ ++;
        int val = GetE();


        if (string_[pos_] == ')')
        {
            pos_ ++;
        }
        else 
        {
            THROW(SYNTAX_ERROR, "Alone standing [ ( - bracket]", nullptr);
        }

        SPACE_CORRECTION

        return val;
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
int Parser::GetT()
{
    int val1 = GetP();
    while ((string_[pos_] == '*') || (string_[pos_] == '/'))
    {
        char op  = string_[pos_];

        pos_++;
        int val2 = GetP();

        if (op == '*')
        {
            val1 *= val2;
        }
        else
        {
            val1 /= val2;
        }
    }

    return val1;
}

/* -------------------------------------------------------
 * @about
 *        'Get Expression', Maestro of '+' and '-'
 *        Foreman in our project
 *        Calculating expressions (+ or -)
 *
 *
 /--------------------------------------------------------*/
int Parser::GetE()
{
    int val1 = GetT();
    while ((string_[pos_] == '+') || (string_[pos_] == '-'))
    {
        char op  = string_[pos_];

        pos_++;
        int val2 = GetT();
        
        if (op == '+')
        {
            val1 += val2;
        }
        else 
        {
            val1 -= val2;
        }
    }

    return val1;
}


/* -------------------------------------------------------
 * @about
 *        Parser, calls functions
 *        Top manager in black Mercedes
 *        Calculating expressions (+ or -)
 *
 *
 /--------------------------------------------------------*/
int Parser::Pars()
{
    SPACE_CORRECTION

    int val = GetE();

    if (string_[pos_] == 0)
    {
        return val;
    }
    else
    {
        printf("Incorrect symbol! [%s]\n", string_ + pos_);
        THROW(SYNTAX_ERROR, "Incorrect symbol!", nullptr);
    }
}




#endif //PARSER_CPP