#include <iostream>

/* way to switch-on Lab-mode*/
#define LAB_KILLER

#include "vector.h"


#undef LAB_KILLER

int main()
{
    try
    {
        FILE *dots = fopen("dots.tex", "w");

        printf("Type number of dots\n");
        int n = 0;
        cin >> n;

        Vector<Point> func(n);

        printf("Type dots:\n");
        for (int i = 0; i < n; i++) {
            cin >> func[i];
        }

        func.get_dots(dots, CATMULL_ROM, 0.01);

        fclose(dots);
        return 0;
    }
    catch (Acorn *acorn){
        acorn->tell_user();

    }
}