#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

const double START = 0.0;
const double END = 6.0;
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

std::vector<double> trigonometric(const std::vector<point>& values, int degree, bool ifSIN){
    std::vector<double> coefficients(degree + 1, 0);

    for(int i = 0; i <= degree; i++){
        double sum = 0;
        for (auto value : values) {
            if (ifSIN)
                sum += value.y * sin(i * value.x);
            else
                sum += value.y * cos(i * value.x);
        }
        coefficients[i] = 2 * sum / values.size();
    }
    return coefficients;
}

double approxHelper(double x, const std::vector<double>& coeffCOS, const std::vector<double>& coeffSIN){
    double result = coeffCOS[0] / 2;
    for (int i = 1; i < coeffCOS.size(); i++)
        result += (coeffCOS[i]*cos(i*x) +  coeffSIN[i]*sin(i*x));
    return result;
}

std::vector<point> approximation(const std::vector<point>& values, const std::vector<double>& coeffCOS, const std::vector<double>& coeffSIN){
    std::vector<point> result;
    for(point item : values){
        point point{};
        point.x = item.x;
        point.y = approxHelper(item.x, coeffCOS, coeffSIN);
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
                std::vector<double> coeffCOS = trigonometric(values, degree, false);
                std::vector<double> coeffSIN = trigonometric(values, degree, true);
                std::vector<point> results = approximation(values, coeffCOS, coeffSIN);
                double error;
                if(func == "f1")
                    error = totalError(function, results);
                else
                    error = totalError(function2, results);
                std::cout << "P " <<func << ": points number: " << number << ", degree: " << degree << ", error: " << error
                          << std::endl;
                file.open(path + "_" + func + "P_" + std::to_string(number) + "_" + std::to_string(degree) + "_COS" + fileExtension);
                for (double coefficient : coeffCOS)
                    file << coefficient << std::endl;
                file.close();
                file.open(path + "_" + func + "P_" + std::to_string(number) + "_" + std::to_string(degree) + "_SIN" + fileExtension);
                for (double coefficient : coeffSIN)
                    file << coefficient << std::endl;
                file.close();
            }
        }
    }

    system("python plot.py");

    return 0;

}
