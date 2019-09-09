#include "Matrix.h"
#include <iostream>
#include <list>
int main(){
    Matrix<int> mat(4, 4, 10);
    Matrix<int> mat2(4, 4, 2);
    mat = mat.multiply(mat2);
    mat.print(std::cout);
    mat = mat.multiply(2);
    mat.print(std::cout);
    //mat.colPrint(std::cout);
    std::cout<<"Done";

    return 0;

}
