#include <vector>
#include <iostream>

template <typename T> class AGHMatrix
{
private:
    std::vector<std::vector<T>> matrix;
    unsigned rows;
    unsigned cols;

public:
    explicit AGHMatrix(const std::vector<std::vector<T>>& matrix);
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

    // Access the row and column sizes
    unsigned get_rows() const;
    unsigned get_cols() const;

    AGHMatrix<T> Jacoby(const AGHMatrix<T>& inputMatrix, unsigned iterations) const;
    AGHMatrix<T> GaussSiedel(const AGHMatrix<T>& inputMatrix, unsigned iterations) const;
    AGHMatrix<T> SOR(const AGHMatrix<T>& inputMatrix, unsigned iterations) const;
};

// Parameter Constructor
template<typename T>
AGHMatrix<T>::AGHMatrix(const std::vector<std::vector<T>>& mat)
{
    matrix.resize(mat.size());
    for (unsigned i = 0; i < mat.size(); i++)
    {
        matrix[i].resize(mat[i].size());
        for(unsigned j = 0; j < mat[i].size(); j++)
        {
            matrix[i][j] = mat[i][j];
        }
    }
    rows = matrix.size();
    cols = matrix[1].size();
}

// Copy Constructor
template<typename T>
AGHMatrix<T>::AGHMatrix(const AGHMatrix<T>& rhs)
{
    matrix = rhs.matrix;
    rows = rhs.get_rows();
    cols = rhs.get_cols();
}

// Get the number of rows of the matrix
template<typename T>
unsigned AGHMatrix<T>::get_rows() const
{
    return this->rows;
}

// Get the number of columns of the matrix
template<typename T>
unsigned AGHMatrix<T>::get_cols() const
{
    return this->cols;
}

// Assignment Operator
template<typename T>
AGHMatrix<T>& AGHMatrix<T>::operator=(const AGHMatrix<T>& rhs)
{
    if (&rhs == this)
        return *this;

    unsigned new_rows = rhs.get_rows();
    unsigned new_cols = rhs.get_cols();

    matrix.resize(new_rows);
    for (unsigned i=0; i<matrix.size(); i++)
    {
        matrix[i].resize(new_cols);
    }

    for (unsigned i=0; i<new_rows; i++)
    {
        for (unsigned j=0; j<new_cols; j++)
        {
            matrix[i][j] = rhs(i, j);
        }
    }
    rows = new_rows;
    cols = new_cols;

    return *this;
}

// Access the individual elements
template<typename T>
T& AGHMatrix<T>::operator()(const unsigned& row, const unsigned& col)
{
    return this->matrix[row][col];
}

// Access the individual elements (const)
template<typename T>
const T& AGHMatrix<T>::operator()(const unsigned& row, const unsigned& col) const
{
    return this->matrix[row][col];
}

// Addition of two matrices
template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator+(const AGHMatrix<T>& rhs)
{
    if(this->get_cols() != rhs.get_cols() || this->get_rows() != rhs.get_rows()){
        std::cout<<"error adding";
        exit(-1);
    }
    else{
        AGHMatrix<typeof(this->matrix[0][0])> mat3 (this->get_rows(), this->get_cols(), 0);
        for (int i = 0; i < this->get_rows(); i++) {
            for (int j = 0; j < this->get_cols(); j++) {
                mat3.matrix[i][j] = this->matrix[i][j]+rhs.matrix[i][j];
            }
        }
        return mat3;
    }
}

// Left multiplication of this matrix and another
template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator*(const AGHMatrix<T>& rhs)
{
    if(this->get_cols() != rhs.get_rows()){
        std::cout<<"error multiplying";
        exit(-1);
    }
    else{
        AGHMatrix<typeof(this->matrix[0][0])> mat3 (this->get_rows(), rhs.get_cols(), 0);
        for (int i = 0; i < this->get_rows(); i++) {
            for (int j = 0; j < rhs.get_cols(); j++) {
                for(int k = 0 ; k < this->get_cols(); k++){
                    mat3.matrix[i][j] += this->matrix[i][k]*rhs.matrix[k][j];
                }
            }
        }
        return mat3;
    }
}

// Printing matrix
template<typename T>
std::ostream& operator<<(std::ostream& stream, const AGHMatrix<T>& matrix)
{
    for (int i=0; i<matrix.get_rows(); i++)
    {
        for (int j=0; j<matrix.get_cols(); j++)
        {
            stream << matrix(i,j) << ", ";
        }
        stream << std::endl;
    }
    stream << std::endl;
}