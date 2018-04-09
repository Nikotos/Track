#include <iostream>

#include "Parser.h"

using namespace std;

int main() {
    try{
        Parser p(" 4 + ( 8 + 8 )");
        printf("%d", p.Pars());

    }
    catch(Acorn * acorn)
    {
        acorn->tell_user();
    }
    return 0;
}