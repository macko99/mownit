#include "aghMatrix.h"
#include <iostream>

int main() 
{
    AGHMatrix<double> mat1(5, 5, 1.2);
    AGHMatrix<double> mat2(5, 5, 2.8);

    AGHMatrix<double> mat3 = mat1 + mat2;
    std::cout << mat3;
    mat3 = mat1 * mat2;
    std::cout << mat3;

    std::vector<std::vector<double>> init { { 11.0, 2.0, 3.0 },
                                            { 4.0, 5.0, 6.0 },
                                            { 17.0, 8.0, 9.0 } };
    AGHMatrix<double> mat4(init);

    std::cout <<std::endl <<mat4.is_symmetric()<<std::endl;
    std::cout <<std::endl <<mat4.determinant()<<std::endl;
    std::cout <<std::endl <<mat4.transpose()<<std::endl;

    std::vector<std::vector<double>> init_LU {{ 5.0, 3.0, 2.0 },
                                              { 1.0, 2.0, 0.0 },
                                              { 3.0, 0.0, 4.0 }};
    AGHMatrix<double> mat5(init_LU);


    std::cout << mat5.LU_decomposition().first;
    std::cout << mat5.LU_decomposition().second;

    std::vector<std::vector<double>> init_Cholesky {{ 4, 12, -16 },
                                                    { 12, 37, -43 },
                                                    { -16, -43, 98 }};
    AGHMatrix<double> mat6(init_Cholesky);

    std::cout << mat6.Cholesky_decomposition().first;
    std::cout << mat6.Cholesky_decomposition().second;


    std::vector<std::vector<double>> init_Gauss  {{1, 2, -1, 5},
                                                  {3,4,1, 9},
                                                  {2, -2, 3, -1}};
    AGHMatrix<double> mat7(init_Gauss);
    mat7.Gauss();
    std::cout << mat7;

    std::vector<std::vector<double>> init_Jacobi  {{ 10, -2, -1, -1, 3},
                                                  {-2, 10, -1, -1, 15},
                                                  {-1, -1, 10, -2, 27},
                                                  { -1, -1, -2, 10, -9}};
    AGHMatrix<double> mat8(init_Gauss);
    std::cout <<mat8.Jacobi(100);

    return 0;
}