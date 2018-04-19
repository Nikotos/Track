#ifndef PARSER_CPP
#define PARSER_CPP

#include "Parser.h"



/*=========================================================================================================
 *
 *
 *                                          Parser Functions
 *
 *
 /==========================================================================================================*/



Parser::Parser()
{
    var_list_ = new Var_list(MIN_VAR_LIST_SIZE);
}


Parser::Parser(const char* str)
{
    string_ = str;
    pos_ = 0;

    var_list_ = new Var_list(MIN_VAR_LIST_SIZE);
}


Parser::~Parser()
{
    delete [] heap_;
    heap_ = nullptr;

    delete [] text_;
    text_ = nullptr;

    delete var_list_;

}
/* -------------------------------------------------------
 * @about
 *        Macros for avoiding spaces
 *
 /--------------------------------------------------------*/
#define SPACE_CORRECTION\
    while (string_[pos_] == ' ')\
    {\
        pos_++;\
    }


/* -------------------------------------------------------
 * @about
 *        Get Variable, worker's slave
 *        We call him, when situation is really bad.....
 *
 /--------------------------------------------------------*/

#define IS_LETTER\
    ( ((string_[pos_] >= 'a') && (string_[pos_] <= 'z'))    \
    || ((string_[pos_] >= 'A') && (string_[pos_] <= 'Z'))   \
    || ((string_[pos_] >= 'а') && (string_[pos_] <= 'я'))   \
    || ((string_[pos_] >= 'А') && (string_[pos_] <= 'Я'))  \
    || (string_[pos_] == '_')  )


Node* Parser::GetV()
{
    SPACE_CORRECTION


    var_list_->clean_name_buffer();


    for (int i = 0; IS_LETTER; pos_++, i++)
    {
        var_list_->name_buffer_[i] = string_[pos_];
    }

    SPACE_CORRECTION

    /* such explicit form of code for clarity of code*/
    /* (to upgrade later) */
    if(var_list_->is_in(var_list_->name_buffer_))
    {

        return new Node(var_list_->get_var(var_list_->name_buffer_));
    }
    else
    {
        THROW(SYNTAX_ERROR, "Undefined variable!", nullptr);
    }


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

    if (!IS_DIGIT && IS_LETTER)
    {
        return GetV();
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




/* ---------------------------------------------------------------------
 * @about
 *        Modified 'Get Number', secret agent
 *        Makes 'trash', when notices bracket
 *        (To be honest Calculating expression in brackets)
 *        also, SIN and COS specialist
 *
 *
 /-------------------------------------------------------------------------*/
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

        Node* current_node = nullptr;
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
    else if (strncmp(string_ + pos_, "-(", 1) == 0)
    {
        pos_ += 2;                          // "- (expression in brackets)

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

    Node* current_node = nullptr;
    current_node = GetP();

    while ((string_[pos_] == '*') || (string_[pos_] == '/'))
    {

        Node* node = new Node(OPERATOR_NAMES_DEFAULT);
        node->left_node_ = current_node;

        if (string_[pos_] == '*')
        {
            node->knot_.storage_.oper_ = MULTIPLY;
        }
        else
        {
            node->knot_.storage_.oper_ = DIVIDE;
        }

        pos_++;

        node->right_node_  = GetP();

        current_node = node;

    }

    return current_node;

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

    Node* current_node = nullptr;
    current_node = GetT();

    while ((string_[pos_] == '+') || (string_[pos_] == '-'))
    {

        Node* node = new Node(OPERATOR_NAMES_DEFAULT);
        node->left_node_ = current_node;

        if (string_[pos_] == '+')
        {
            node->knot_.storage_.oper_ = PLUS;
        }
        else
        {
            node->knot_.storage_.oper_ = MINUS;
        }

        pos_++;

        node->right_node_  = GetT();

        current_node = node;

    }

    return current_node;

}


Node* Parser::GetA()
{
    SPACE_CORRECTION

    Node* current_node = nullptr;

    current_node= GetE();

    if (string_[pos_] == '=')
    {
        pos_++;

        SPACE_CORRECTION

        if ((current_node->knot_.type_ != VARIABLE))
        {
            THROW(SYNTAX_ERROR, "Expression before [=] !", nullptr);
        }

        else
        {
            Node* node = new Node(ASSIGN);
            node->left_node_ = current_node;
            node->right_node_ = GetE();

            return node;
        }


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
Command* Parser::Get_command()
{
    SPACE_CORRECTION

    if((strncmp(string_ + pos_, "int", 3) == 0))
    {
        pos_ += 3;

        SPACE_CORRECTION

        SetVar(INTEGER);

        return new Command(VARIABLE_DEFINITION);

    }
    else
    {
        return new Command(GetA());
    }

}



/* -------------------------------------------------------
 * @about
 *        Setting new variable
 *        Adding variable to list of variables to catch some errors
 *
 * @input
 *        type of Variable
 *
 * @output
 *         We add variable with read name to list of variables
 *         (almost output, we work with a pointer)
 *
 /--------------------------------------------------------*/
void Parser::SetVar(enum VAR_TYPES type)
{
    var_list_->clean_name_buffer();


    for (int i = 0; IS_LETTER; pos_++, i++)
    {
        var_list_->name_buffer_[i] = string_[pos_];
    }

    SPACE_CORRECTION

    var_list_->add_variable(type, var_list_->name_buffer_);
}



/* -------------------------------------------------------
 * @about
 *        Fills Function with commands
 *
 * @input
 *        pointer at empty Function
 *
 * @output
 *         Function
 *         (almost output, we work with a pointer)
 *
 /--------------------------------------------------------*/
void Parser::Get_function(Function *func)
{

    for(int i = 0; i < strings_amount_; i++)
    {
        if(text_[i].len_ != 1)
        {
            string_ = text_[i].body_;
            pos_ = 0;

            Command* cmd = nullptr;
            cmd = Get_command();

            func->list_[i].re_set(cmd);

            func->amount_++;


            if (string_[pos_] != 0)
            {
                printf("Incorrect symbol - [%s]!!!!\n", string_ + pos_);
                THROW(SYNTAX_ERROR, "Incorrect symbol!", nullptr);
            }
        }

    }
}





/* -------------------------------------------------------
 * @about
 *        Converts text from file to array of strings
 *
 *
 * @input
 *        file with text
 *
 * @output
 *        array of strings (text_)
 *
 /--------------------------------------------------------*/
void Parser::Read_file(const char *filename)
{
    FILE* input = fopen(filename,"r");

    if (input == nullptr)
    {
        THROW(UNKNOWN_ERROR, "Can't open File!", nullptr);
    }


    const int file_len = sizeof_file(input);

    heap_ = new char [file_len + 1];

    fread (heap_, file_len, sizeof (char), input);

    strings_amount_ = str_amount(heap_);

    text_ = new oak::string [strings_amount_];


    /* splits text from heap_ to
     * sentences and puts it into text_*/
    split_text ();

    fclose(input);
}





/* -------------------------------------------------------
 * @about
 *        Calculates amount of bytes in input file
 *
 *
 /--------------------------------------------------------*/
size_t Parser::sizeof_file(FILE *file)
{
    fseek (file, 0, SEEK_END);
    size_t file_length = ftell (file);

    if (file_length < 0)
    {
        THROW(UNKNOWN_ERROR, "Too big FILE! Change int to long int!", nullptr);
    }

    rewind (file);
    return file_length;
}


/* -------------------------------------------------------
 * @about
 *        Calculates amount of strings in text
 *
 *
 /--------------------------------------------------------*/
size_t Parser::str_amount(const char *heap)
{
    int str_am = 1;

    for(int i = 0; heap[i] != '\0'; i++)
    {
        if (heap[i] == '\n')
        {
            str_am++;
        }

    }
    return str_am;
}


/* -------------------------------------------------------
 * @about
 *        splits text to strings
 *        splits heap_ to text_
 *
 * @input
 *        heap with text
 *
 * @output
 *        array of strings
 *
 /--------------------------------------------------------*/
void Parser::split_text ()
{
    int j = 0; //index for array of strings
    text_[j].body_ = heap_;
    j++;

    int i = 0; //index for heap
    while (heap_[i] != '\0')
    {
        if (heap_[i] == '\n')
        {
            heap_[i] = '\0';
            text_[j - 1].len_ = heap_ + i - text_[j - 1].body_ + 1;

            text_[j].body_ = heap_ + i + 1;
            j++;
        }

        i++;
    }
    text_[j - 1].len_ = heap_ + i - text_[j - 1].body_ + 1;
}

#undef IS_DIGIT
#undef IS_LETTER

#endif //PARSER_CPP
