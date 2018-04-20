#include <iostream>



#include "Parser.h"


using namespace std;

int main() {
    try
    {

        Parser pars;


        pars.Read_file("proga.txt");


        Function* prog = nullptr;

        prog = pars.Get_program();


        prog->print();
    }

    catch (Acorn* acorn)
    {
        acorn->tell_user();
    }
    return 0;
}


