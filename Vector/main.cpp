#include <iostream>
#include "vector.h"

using namespace std;

int main() {
    Vector <double> v1(10);
    Vector <double> v2 (100);
    v2 = v1;
    cout<<v2[7]<<endl;
    return 0;
}
