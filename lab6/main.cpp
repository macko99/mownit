#include "aghMatrix.cpp"
#include <fstream>
std::string fileExtension = ".txt";
std::string path = "results/";
std::ofstream file;
unsigned fileCounter = 0;


template<typename T>
AGHMatrix<T> AGHMatrix<T>::Jacoby(const AGHMatrix<T>& inputMatrix, unsigned iterations) const {

    AGHMatrix<double> X(inputMatrix);
    AGHMatrix<double> Xcopy(inputMatrix);

    if(X.get_cols() != 1) {
        std::cout<<"input matrix must have one column";
        exit(-1);
    }
    if (this->rows != this->cols || matrix.size() != inputMatrix.get_rows()) {
        std::cout<<"matrix must be square, and have as many rows as input matrix";
        exit(-1);
    }
    file.open(path + "J_" + std::to_string(fileCounter%5 + 1) + "_" + std::to_string(iterations) + fileExtension);

    for(unsigned i = 0; i < iterations; i++) {
        for (unsigned row = 0; row < this->rows; row++) {
            double sum = 0;
            for (unsigned col = 0; col < this->cols; col++) {
                if (col != row) {
                    sum += matrix[row][col] * Xcopy(col, 0);
                }
            }
            X(row, 0) = (inputMatrix(row, 0) - sum) / matrix[row][row];
        }
        Xcopy = X;

        double sum = 0;
        for(unsigned j = 0; j < this->rows; j++){
            sum += X(j, 0);
        }
        sum /= this->rows;
        file << sum << std::endl;
    }
    file.close();
    fileCounter++;
    return X;
}

template<typename T>
AGHMatrix<T> AGHMatrix<T>::GaussSiedel(const AGHMatrix<T>& inputMatrix, unsigned iterations) const {

    AGHMatrix<double> X(inputMatrix);
    AGHMatrix<double> Xcopy(inputMatrix);

    if(X.get_cols() != 1) {
        std::cout<<"input matrix must have one column";
        exit(-1);
    }
    if (this->rows != this->cols || matrix.size() != inputMatrix.get_rows()) {
        std::cout<<"matrix must be square, and have as many rows as input matrix";
        exit(-1);
    }
    file.open(path + "GS_" + std::to_string(fileCounter%5 + 1) + "_" + std::to_string(iterations) + fileExtension);

    for(unsigned i = 0; i < iterations; i++) {
        for(unsigned row = 0; row < this->rows; row++) {
            double sum = 0;
            for(unsigned col = 0; col < this->cols; col++) {
                if(col > row) {
                    sum += matrix[row][col] * Xcopy(col, 0);
                }
                if(col < row) {
                    sum += matrix[row][col] * X(col, 0);
                }
            }
            X(row, 0) = (inputMatrix(row, 0) - sum) / matrix[row][row];
        }
        Xcopy = X;

        double sum = 0;
        for(unsigned j = 0; j < this->rows; j++){
            sum += X(j, 0);
        }
        sum /= this->rows;
        file << sum << std::endl;
    }
    file.close();
    fileCounter++;
    return X;
}

template<typename T>
AGHMatrix<T> AGHMatrix<T>::SOR(const AGHMatrix<T>& inputMatrix, unsigned iterations) const {

    double omega = 1.25; //na podstawie: http://marta.certik.cz/NM/Asor.pdf
    AGHMatrix<double> X(inputMatrix);
    AGHMatrix<double> Xcopy(inputMatrix);

    if(X.get_cols() != 1) {
        std::cout<<"input matrix must have one column";
        exit(-1);
    }
    if (this->rows != this->cols || matrix.size() != inputMatrix.get_rows()) {
        std::cout<<"matrix must be square, and have as many rows as input matrix";
        exit(-1);
    }
    file.open(path + "SOR_" + std::to_string(fileCounter%5 + 1) + "_" + std::to_string(iterations) + fileExtension);

    for(unsigned i = 0; i < iterations; i++) {
        for(unsigned row = 0; row < this->rows; row++) {
            double sum = 0;
            for(unsigned col = 0; col < this->cols; col++) {
                if(col > row) {
                    sum += matrix[row][col] * Xcopy(col, 0);
                }
                if(col < row) {
                    sum += matrix[row][col] * X(col, 0);
                }
            }
            X(row, 0) = (1 - omega) * Xcopy(row, 0) + omega * (inputMatrix(row, 0) - sum) / matrix[row][row];
        }
        Xcopy = X;

        double sum = 0;
        for(unsigned j = 0; j < this->rows; j++){
            sum += X(j, 0);
        }
        sum /= this->rows;
        file << sum << std::endl;
    }
    file.close();
    fileCounter++;
    return X;
}

int main(){

    unsigned iterations = 20;

        std::vector<std::vector<double>> init1a {{3.0,  -1.0, 1.0 },
                                                 {-1.0, 3.0,  -1.0 },
                                                 {1.0,  -1.0, 3.0 } };

        std::vector<std::vector<double>> init1b {{-1.0 },
                                                 {7.0 },
                                                 {-7.0 } };

        std::vector<std::vector<double>> sol1 {{1.0 },
                                               {2.0 },
                                               {-2.0 } };

        std::vector<std::vector<double>> nit2a {{5.0, -3.0 },
                                                {1.0, -2.0 } };

        std::vector<std::vector<double>> init2b {{21.0 },
                                                 {7.0 } };

        std::vector<std::vector<double>> sol2 {{3.0 },
                                               {-2.0 } };

        std::vector<std::vector<double>> init3a {{4.0,  -1.0, -0.2, 2.0 },
                                                 {-1.0, 5.0,  0.0,  -2.0 },
                                                 {0.2,  1.0,  10.0, -1.0 },
                                                 {0.0,  -2.0, -1.0, 4.0 } };

        std::vector<std::vector<double>> init3b {{21.6 },
                                                 {36.0 },
                                                 {-20.6 },
                                                 {-11.0 } };

        std::vector<std::vector<double>> sol3 {{7.0 },
                                               {9.0 },
                                               {-3.0 },
                                               {1.0 } };

        std::vector<std::vector<double>> init4a {{5.02, 2.01,  -0.98 },
                                                 {3.03, 6.95,  3.04 },
                                                 {1.01, -3.99, 5.98 }};

        std::vector<std::vector<double>> init4b {{2.05 },
                                                 {-1.02 },
                                                 {0.98 }};

        std::vector<std::vector<double>> sol4 {{0.50774 },
                                               {-0.31141 },
                                               {-0.12966 }};

        std::vector<std::vector<double>> init5a {{1.0, 0.0, 0.0, 0.0, 0.0 },
                                                 {0.0, 1.0, 0.0, 0.0, 0.0 },
                                                 {0.0, 0.0, 1.0, 0.0, 0.0 },
                                                 {0.0, 0.0, 0.0, 1.0, 0.0 },
                                                 {0.0, 0.0, 0.0, 0.0, 1.0 }};

        std::vector<std::vector<double>> init5b {{1.0 },
                                                 {1.0 },
                                                 {1.0 },
                                                 {1.0 },
                                                 {1.0 }};

        std::vector<std::vector<double>> sol5 {{1.0 },
                                               {1.0 },
                                               {1.0 },
                                               {1.0 },
                                               {1.0 }};

        AGHMatrix<double> matrix1a(init1a);
        AGHMatrix<double> matrix1b(init1b);
        AGHMatrix<double> solution1(sol1);

        AGHMatrix<double> matrix2a(nit2a);
        AGHMatrix<double> matrix2b(init2b);
        AGHMatrix<double> solution2(sol2);

        AGHMatrix<double> matrix3a(init3a);
        AGHMatrix<double> matrix3b(init3b);
        AGHMatrix<double> solution3(sol3);

        AGHMatrix<double> matrix4a(init4a);
        AGHMatrix<double> matrix4b(init4b);
        AGHMatrix<double> solution4(sol4);

        AGHMatrix<double> matrix5a(init5a);
        AGHMatrix<double> matrix5b(init5b);
        AGHMatrix<double> solution5(sol5);

        AGHMatrix<double> result1J = matrix1a.Jacoby(matrix1b, iterations);
        AGHMatrix<double> result2J = matrix2a.Jacoby(matrix2b, iterations);
    AGHMatrix<double> result3J = matrix3a.Jacoby(matrix3b, iterations);
    AGHMatrix<double> result4J = matrix4a.Jacoby(matrix4b, iterations);
    AGHMatrix<double> result5J = matrix5a.Jacoby(matrix5b, iterations);

        AGHMatrix<double> result1GS = matrix1a.GaussSiedel(matrix1b, iterations);
    AGHMatrix<double> result2GS = matrix2a.GaussSiedel(matrix2b, iterations);
    AGHMatrix<double> result3GS = matrix3a.GaussSiedel(matrix3b, iterations);
    AGHMatrix<double> result4GS = matrix4a.GaussSiedel(matrix4b, iterations);
    AGHMatrix<double> result5GS = matrix5a.GaussSiedel(matrix5b, iterations);

        AGHMatrix<double> result1SOR = matrix1a.SOR(matrix1b, iterations);
        AGHMatrix<double> result2SOR = matrix2a.SOR(matrix2b, iterations);
        AGHMatrix<double> result3SOR = matrix3a.SOR(matrix3b, iterations);
        AGHMatrix<double> result4SOR = matrix4a.SOR(matrix4b, iterations);
        AGHMatrix<double> result5SOR = matrix5a.SOR(matrix5b, iterations);

    std::cout << "test 1: real:" << std::endl << solution1;
    std::cout << "Jacoby:" << std::endl << result1J;
    std::cout << "Gauss-Siedel:" << std::endl << result1GS;
    std::cout << "SOR:" << std::endl << result1SOR;

    std::cout << "test 2: real:" << std::endl << solution2;
    std::cout << "Jacoby:" << std::endl << result2J;
    std::cout << "Gauss-Siedel:" << std::endl << result2GS;
    std::cout << "SOR:" << std::endl << result2SOR;

    std::cout << "test 3: real:" << std::endl << solution3;
    std::cout << "Jacoby:" << std::endl << result3J;
    std::cout << "Gauss-Siedel:" << std::endl << result3GS;
    std::cout << "SOR:" << std::endl << result3SOR;

    std::cout << "test 4: real:" << std::endl << solution4;
    std::cout << "Jacoby:" << std::endl << result4J;
    std::cout << "Gauss-Siedel:" << std::endl << result4GS;
    std::cout << "SOR:" << std::endl << result4SOR;

    std::cout << "test 5: real:" << std::endl << solution5;
    std::cout << "Jacoby:" << std::endl << result5J;
    std::cout << "Gauss-Siedel:" << std::endl << result5GS;
    std::cout << "SOR:" << std::endl << result5SOR;

    file.open(path + "1_" + std::to_string(iterations) + fileExtension);
    for (int row = 0; row < solution1.get_rows(); row++){
        file<< solution1(row, 0)<<std::endl;
    }
    file.close();
    file.open(path + "2_" + std::to_string(iterations) + fileExtension);
    for (int row = 0; row < solution2.get_rows(); row++){
        file<< solution2(row, 0) <<std::endl;
    }
    file.close();
    file.open(path + "3_" + std::to_string(iterations) + fileExtension);
    for (int row = 0; row < solution3.get_rows(); row++){
        file<< solution3(row, 0)<<std::endl;
    }
    file.close();
    file.open(path + "4_" + std::to_string(iterations) + fileExtension);
    for (int row = 0; row < solution4.get_rows(); row++){
        file<< solution4(row, 0)<<std::endl;
    }
    file.close();
    file.open(path + "5_" + std::to_string(iterations) + fileExtension);
    for (int row = 0; row < solution5.get_rows(); row++){
        file<< solution5(row, 0)<<std::endl;
    }
    file.close();

    system("python plot.py");
    return 0;
}