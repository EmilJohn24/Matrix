#include "Matrix.h"
#include <iostream>
#include <list>
int main(){
    Matrix<int> mat1(100, 100, 1);
    mat1 = 2 * mat1;
    //mat1.print(std::cout);
    //mat.colPrint(std::cout);
    std::cout<<"Done";

    return 0;

}
