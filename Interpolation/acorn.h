#ifndef ACORN_H
#define ACORN_H

/*------------------------------------------------------------------------
 *
 *  Exception class "Acorn"
 *  Acorn - easy and nicely to throw
 *  Acorn - full range of information will thrown directly "on yor head"
 *
 /------------------------------------------------------------------------*/
enum ERRORS {
    MEMORY_ALLOCATION_ERROR = 0,
    MEMORY_ACCES_ERROR,
    INVALID_ARGUMENT,
    OUT_OF_RANGE,
    LOGIC_ERROR,
    UNKNOWN_ERROR = 42
};

class Acorn {
public:
    enum ERRORS errcode_ = UNKNOWN_ERROR;
    const char* message_;
    const char* function_name_;
    const char* file_name_;
    int line_;
    Acorn* Acorn_pointer_ = nullptr;

    inline Acorn(enum ERRORS errcode,
          const char * message,
          const char *function_name,
          const char* file_name,
          int line,
          Acorn* Acorn_pointer);

    inline void write_log(const char* LOG_FILE_NAME);

    inline void write_log();

    void tell_user();
};

inline Acorn::Acorn(enum ERRORS errcode,
             const char * message,
             const char *function_name,
             const char* file_name,
             int line,
             Acorn* Acorn_pointer):
        errcode_(errcode),
        message_(message),
        function_name_(function_name),
        file_name_(file_name),
        line_(line),
        Acorn_pointer_(Acorn_pointer)
{
    write_log("acorn_log.txt");
}

inline void Acorn::write_log(const char *LOG_FILE_NAME)
{
    FILE* log = fopen(LOG_FILE_NAME, "a");

    Acorn* acorn = this;
    while(acorn != nullptr) {
        fprintf(log, "Error in FILE [%s]\n"
                     "in FUNCTION [%s]\n"
                     "in LINE [%d]\n"
                     "Error code is [%d]\n"
                     "Message is [%s] \n",
                     acorn->file_name_,
                     acorn->function_name_, 
                     acorn->line_,
                     acorn->errcode_,
                     acorn->message_);
        
        if (acorn->Acorn_pointer_ != nullptr) {
            fprintf(log, "More Info.....\n\n");
        }
        acorn = acorn->Acorn_pointer_;
    }
}

inline void Acorn::write_log()
{
    write_log("acorn_log.txt");
}

inline void Acorn::tell_user() {
    Acorn* acorn = this;
    while(acorn != nullptr) {
        printf("Error in FILE [%s]\n"
               "in FUNCTION [%s]\n"
               "in LINE [%d]\n"
               "Error code is [%d]\n"
               "Message is [%s] \n",
               acorn->file_name_,
               acorn->function_name_,
               acorn->line_,
               acorn->errcode_,
               acorn->message_);

        if (acorn->Acorn_pointer_ != nullptr) {
            printf("More Info.....\n\n");
        }
        acorn = acorn->Acorn_pointer_;
    }
}

#endif //ACORN_H