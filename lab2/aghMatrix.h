#pragma once 

#include <vector>
#include <iostream>

template <typename T> class AGHMatrix 
{
private:
    std::vector<std::vector<T>> matrix;
    unsigned rows;
    unsigned cols;

public:
    AGHMatrix(const std::vector<std::vector<T>>& matrix);
    AGHMatrix(unsigned _rows, unsigned _cols, const T& _initial);
    AGHMatrix(const AGHMatrix<T>& rhs);
    virtual ~AGHMatrix() = default;

    // Operator overloading, for "standard" mathematical matrix operations                                                                                                                                                          
    AGHMatrix<T>& operator=(const AGHMatrix<T>& rhs);

    // Matrix mathematical operations                                                                                                                                                                                               
    AGHMatrix<T> operator+(const AGHMatrix<T>& rhs);
    AGHMatrix<T> operator*(const AGHMatrix<T>& rhs);

    // Access the individual elements                                                                                                                                                                                               
    T& operator()(const unsigned& row, const unsigned& col);
    const T& operator()(const unsigned& row, const unsigned& col) const;
    
    // Printing matrix
    std::ostream& operator<<(const AGHMatrix<T>& matrix);

    bool is_symmetric();
    double determinant();
    std::pair<AGHMatrix<T>, AGHMatrix<T>> LU_decomposition();
    std::pair<AGHMatrix<T>, AGHMatrix<T>> Cholesky_decomposition();
    AGHMatrix<T> transpose();
    void Gauss();
    AGHMatrix<T> Jacobi(int iterations);

    // Access the row and column sizes                                                                                                                                                                                              
    unsigned get_rows() const;
    unsigned get_cols() const;
};
#include "aghMatrix.cpp"
