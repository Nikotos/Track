#include <iostream>



#include "Parser.h"


using namespace std;

int main() {
    try
    {

        Parser pars;


        pars.Read_file("proga.txt");


        Function func(pars.strings_amount_ - 1);


        pars.Get_function(&func);

        func.print();
    }

    catch (Acorn* acorn)
    {
        acorn->tell_user();
    }
    return 0;
}


