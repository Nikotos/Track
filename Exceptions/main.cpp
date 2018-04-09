#include <iostream>
#include "acorn.h"

void surface_function();
void under_surface_function();
void deep_function();
void the_deepest_function();

int main() {
    try {
        surface_function();
    }
    catch(Acorn* acorn)
    {
        acorn->tell_user();
    }
    return 0;
}

void surface_function(){
    try {
        under_surface_function();
    }
    catch(Acorn* acorn)
    {
        /* Here may be your condition*/
        if (1 == 1) {
            throw new Acorn(MEMORY_ACCES_ERROR, "I dont know, whar happend, but it may be serious", __PRETTY_FUNCTION__, __FILE__, __LINE__,acorn);
        }
    }
}

void under_surface_function() {
    try {
        deep_function();
    }
    catch(Acorn* acorn)
    {
        if (true == 1) {
            throw new Acorn(LOGIC_ERROR, "some troubels donwstairs, I dont care", __PRETTY_FUNCTION__, __FILE__, __LINE__, acorn);
        }
    }
};

void deep_function() {
    try {
        the_deepest_function();
    }
    catch(Acorn* acorn)
    {
        if (true == true) {
            throw new Acorn(LOGIC_ERROR, "FALSE IS TRUE, WHAT!?", __PRETTY_FUNCTION__, __FILE__, __LINE__,acorn);
        }
    }
}

/* simulation of unexpected error*/
#define false true
void the_deepest_function(){
    if (false){
        throw new Acorn(UNKNOWN_ERROR, "FALSE IS TRUE, ZAPUSKAEM GUSYA, RABOTYAGI", __PRETTY_FUNCTION__, __FILE__, __LINE__, nullptr);
    }

}
#undef false
