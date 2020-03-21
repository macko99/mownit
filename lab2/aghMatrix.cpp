#include "aghMatrix.h"
#include <cmath>

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

// Parameter Constructor                                                                                                                                                      
template<typename T>
AGHMatrix<T>::AGHMatrix(unsigned _rows, unsigned _cols, const T& _initial) 
{
  matrix.resize(_rows);
  for (unsigned i=0; i<matrix.size(); i++) 
  {
    matrix[i].resize(_cols, _initial);
  }
  rows = _rows;
  cols = _cols;
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

template<typename T>
bool AGHMatrix<T>::is_symmetric()
{
    if(this->get_cols() == this->get_rows()){
        for (unsigned i=0; i<this->get_rows(); i++) {
            for (unsigned j = 0; j < this->get_cols(); j++) {
                if (i != j && this->matrix[i][j] != this->matrix[j][i])
                    return false;
            }
        }
        return true;
    }
    return false;
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

template<typename T>
AGHMatrix<T> AGHMatrix<T>::transpose() {
    if(this->is_symmetric())
        return *this;

    AGHMatrix<typeof(this->matrix[0][0])> mat3 (this->get_cols(), this->get_rows(), 0);
    for (int i = 0; i < this->get_rows(); i++) {
        for (int j = 0; j < this->get_cols(); j++) {
            mat3.matrix[j][i] = this->matrix[i][j];
        }
    }
    return mat3;
}

template<typename T>
std::pair<AGHMatrix<T>, AGHMatrix<T>> AGHMatrix<T>::Cholesky_decomposition() {
    if(!this->is_symmetric()){
        std::cout<<"error -> matrix must be symmetric"<<std::endl;
        exit(-1);
    }
    AGHMatrix<typeof(this->matrix[0][0])> lower (this->get_rows(), this->get_cols(), 0);
    AGHMatrix<typeof(this->matrix[0][0])> upper (this->get_rows(), this->get_cols(), 0);

    for (int i = 0; i < this->get_cols(); i++) {
        for (int j = 0; j <= i; j++) {
            typeof(this->matrix[0][0]) sum = 0;
            if (j == i){
                for (int k = 0; k < j; k++)
                    sum += pow(lower.matrix[j][k], 2);
                lower.matrix[j][j] = sqrt(this->matrix[j][j] - sum);
            }
            else {
                for (int k = 0; k < j; k++)
                    sum += (lower.matrix[i][k] * lower.matrix[j][k]);
                lower.matrix[i][j] = (this->matrix[i][j] - sum) / lower.matrix[j][j];
            }
        }
    }
    upper = lower.transpose();
    std::pair<AGHMatrix<T>, AGHMatrix<T>> pair = std::make_pair(lower, upper);
    return pair;
}

template<typename T>
std::pair<AGHMatrix<T>, AGHMatrix<T>> AGHMatrix<T>::LU_decomposition() {
    if(this->get_rows() != this->get_cols()){
        std::cout<<"error -> matrix must be square"<<std::endl;
        exit(-1);
    }
    AGHMatrix<typeof(this->matrix[0][0])> lower (this->get_rows(), this->get_cols(), 0);
    AGHMatrix<typeof(this->matrix[0][0])> upper (this->get_rows(), this->get_cols(), 0);

    for (int i = 0; i < this->get_cols(); i++) {
        for (int k = i; k < this->get_cols(); k++) {
            typeof(this->matrix[0][0]) sum = 0;
            for (int j = 0; j < i; j++)
                sum += (lower.matrix[i][j] * upper.matrix[j][k]);
            upper.matrix[i][k] = this->matrix[i][k] - sum;
        }
        for (int k = i; k < this->get_cols(); k++) {
            if (i == k)
                lower.matrix[i][i] = 1;
            else {
                typeof(this->matrix[0][0]) sum = 0;
                for (int j = 0; j < i; j++)
                    sum += (lower.matrix[k][j] * upper.matrix[j][i]);
                lower.matrix[k][i] = (this->matrix[k][i] - sum) / upper.matrix[i][i];
            }
        }
    }
    std::pair<AGHMatrix<T>, AGHMatrix<T>> pair = std::make_pair(lower, upper);
    return pair;
}

template<typename T>
void AGHMatrix<T>::Gauss() {
    for (int i = 0; i < this->get_rows() - 1; i++) {
        for (int j = i+1; j < this->get_rows(); j++) {
            if(this->matrix[i][i] == 0) {
                std::cout<<"error -> dividing by 0";
                return;
            }
            double factor = -this->matrix[j][i] / this->matrix[i][i];
            for (int k = i; k < this->get_cols(); k++)
                this->matrix[j][k] += factor * this->matrix[i][k];
        }
    }
    for (int i = this->get_rows()-1; i >= 0; i--) {
        for (int j =this->get_rows()-1; j > i; j--) {
            this->matrix[i][this->get_rows()] -= this->matrix[i][j] * this->matrix[j][this->get_rows()];
            this->matrix[i][j] = 0;
        }
        if(this->matrix[i][i] == 0) {
            std::cout<<"error -> dividing by 0";
            return;
        }
        this->matrix[i][this->get_rows()] /= this->matrix[i][i];
        this->matrix[i][i] = 1;
    }
}

template<typename T>
double AGHMatrix<T>::determinant() {
    {
        double tmp1, tmp2, result = 1, idx, counter = 1;
        int temp[this->get_rows() + 1];
        for(int i = 0; i < this->get_rows(); i++){
            idx = i;
            while(this->matrix[idx][i] == 0 && idx < this->get_rows()){
                idx++;
            }
            if(idx == this->get_rows()){
                continue;
            }
            if(idx != i){
                for(int j = 0; j < this->get_rows(); j++){
                    std::swap(this->matrix[idx][j], this->matrix[i][j]);
                }
                result *= pow(-1, idx - i);
            }
            for(int j = 0; j < this->get_rows(); j++){
                temp[j] = this->matrix[i][j];
            }
            for(int j = i+1; j < this->get_rows(); j++){
                tmp1 = temp[i];
                tmp2 = this->matrix[j][i];
                for(int k = 0; k < this->get_rows(); k++){
                    this->matrix[j][k] = (tmp1 * this->matrix[j][k]) - (tmp2 * temp[k]);
                }
                counter *= tmp1;
            }
        }
        for(int i = 0; i < this->get_rows(); i++){
            result *= this->matrix[i][i];
        }
        return (result / counter);
    }
}

template<typename T>
AGHMatrix<T> AGHMatrix<T>::Jacobi(int iterations) {
    double sum = 0;
    for(int i = 0; i < this->get_rows(); i++){
        for(int j=0; j < this->get_rows(); j++) {
            sum += this->matrix[i][j];
        }
        if(!(2 * this->matrix[i][i] > sum)) {
            std::cout<<"error -> matrix must be strictly diagonally dominant";
            exit(-1);
        }
        sum = 0;
    }
    AGHMatrix<double> result (1, this->get_rows(), 0);
    double *tmp = (double*) malloc(this->get_rows() * sizeof(double));

    for(int m = 0; m < iterations; m++) {
        for (int i = 0; i < this->get_rows(); i++) {
            tmp[i] = this->matrix[i][this->get_rows()];
            for (int j = 0; j < this->get_rows(); j++) {
                if (i != j) {
                    tmp[i] -= this->matrix[i][j] * result.matrix[0][j];
                }
            }
        }
        for (int i = 0; i < this->get_rows(); i++) {
            result.matrix[0][i] = tmp[i] / this->matrix[i][i];
        }
    }
    return result;
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