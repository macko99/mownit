#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

const double START = 0;
const double END = 10.0;
const int degrees[4] = {4, 7, 10, 20};
const int points[5] = {5, 10, 20, 50, 100};
const std::string files[2] = {"f1", "f2"};

struct point {
    double x;
    double y;
};

double function(double x) {
    return exp(cos(x));
}
double function2(double x) {
    return sin(x)*exp(-x/M_PI);
}

std::vector<point> getPoints(double function(double x), unsigned pointsNumber) {
    std::vector<point> values;
    double interval = (END - START) / (pointsNumber - 1);
    for (int i = 0; i < pointsNumber; i++) {
        point point{};
        point.x = START + interval * i;
        point.y = function(point.x);
        values.push_back(point);
    }
    return values;
}

std::vector<double> polynomial(const std::vector<point>& values, int degree){
    std::vector<double> sigmaX(2*degree+1, 0);
    std::vector<double> sigmaY(degree+1, 0);
    std::vector<double> coefficients(degree + 1, 0);
    double normalMatrix[degree + 1][degree + 2];

    for (int i = 0; i < sigmaX.size(); i++)
        for (point value : values)
            sigmaX[i] += pow(value.x, i);

    for (int i = 0; i < sigmaY.size(); i++)
        for (point value : values)
            sigmaY[i] += pow(value.x, i) * value.y;

    for (int i = 0; i < degree+1; i++) {
        for (int j = 0; j < degree + 1; j++)
            normalMatrix[i][j] = sigmaX[i + j];
        normalMatrix[i][degree + 1] = sigmaY[i];
    }

    for (int i = 0; i < degree; i++)
        for (int k = i+1; k < degree + 1; k++){
            double tmp = normalMatrix[k][i] / normalMatrix[i][i];
            for (int j = 0; j <= degree + 1; j++)
                normalMatrix[k][j] -= tmp * normalMatrix[i][j];
        }

    for (int i = degree; i >= 0; i--){
        coefficients.at(i) = normalMatrix[i][degree+1];
        for (int j = 0; j < degree + 1; j++)
            if (j != i)
                coefficients.at(i) -= normalMatrix[i][j] * coefficients.at(j);
        coefficients.at(i) /= normalMatrix[i][i];
    }

    return coefficients;
}

double approxHelper(double x, const std::vector<double>& coefficient){
    double result = 0;
    for (int i = 0; i < coefficient.size(); i++)
        result += coefficient[i]*std::pow(x, i);
    return result;
}

std::vector<point> approximation(const std::vector<point>& values, const std::vector<double>& coefficients)
{
    std::vector<point> result;
    for(point item : values){
        point point{};
        point.x = item.x;
        point.y = approxHelper(item.x, coefficients);
        result.push_back(point);
    }
    return result;
}
double totalError(double function(double x), const std::vector<point>& result) {
    double error = 0.0;
    for(point item : result){
        error += std::abs(function(item.x) - item.y);
    }
    return error;
}
int main(){

    std::string fileExtension = ".txt";
    std::string path = "results/results";
    std::ofstream file;

    for (const std::string& func : files) {
        for (int number : points) {
            file.open(path + "_" + func + "_" + std::to_string(number) + fileExtension);
            std::vector<point> values;
            if (func == "f1")
                values = getPoints(function, number);
            else
                values = getPoints(function2, number);
            for (point value : values)
                file << value.x << " " << value.y << std::endl;
            file.close();

            for (int degree : degrees) {
                file.open(path + "_" + func + "P_" + std::to_string(number) + "_" + std::to_string(degree) + fileExtension);
                std::vector<double> coefficients = polynomial(values, degree);
                std::vector<point> results = approximation(values, coefficients);
                double error;
                if(func == "f1")
                    error = totalError(function, results);
                else
                    error = totalError(function2, results);
                std::cout << "P " <<func << ": points number: " << number << ", degree: " << degree << ", error: " << error
                          << std::endl;
                for (double coefficient : coefficients)
                    file << coefficient << std::endl;
                file.close();
            }
        }
    }

    system("python plot.py");

    return 0;

}
