#include "Matrix.h"
#include <iostream>
#include <list>
int main(){
    Matrix<int> mat(100, 100, 10);
    Matrix<int> mat2(100, 100, 2);
    Matrix<double> mat3(100, 100, 2.0);
    Matrix<double> mat4(200, 200, 3.0);
    mat.multiply(mat2);
    mat3.multiply(mat4);
    //mat.colPrint(std::cout);
    std::cout<<"Done";

    return 0;

}
