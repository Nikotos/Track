#include <iostream>

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include "Parser.h"

using namespace std;

int main() {
    try
    {
        Parser pars("cos(8.0 - 7) * 9");
        Tree tree;

        pars.Get_pars_tree(&tree);

        tree.print();
    }

    catch (Acorn* acorn)
    {
        acorn->tell_user();
    }
    return 0;
}
