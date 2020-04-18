#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

const int STEPS = 2000;
const double START = -5.0;
const double END = 5.0;
const double LENGTH = 10.0;
const int pointsNumber[10] = {2, 3, 5, 7, 10, 12, 15, 20, 30, 35};

struct point {
    double x;
    double y;
};

double function(double x) {
    return exp(cos(x));
}

double derivative(double x) {
    return -sin(x) * exp(cos(x));
}

std::vector<point> getPoints(double function(double x), int pointsNumber) {
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

std::vector<point> getChebyshevPoints(double function(double), int pointsNumber) {
    std::vector<point> values;
    for (int k = pointsNumber - 1; k >= 0; k--) {
        point point{};
        point.x = LENGTH / 2 * cos((M_PI * (2 * k + 1)) / (2 * (pointsNumber)));
        point.y = function(point.x);
        values.push_back(point);
    }
    return values;
}

double lagrangeInPoint(std::vector<point> values, double xi) {
    int n = values.size();
    double result = 0;
    for (int i = 0; i < n; i++) {
        double yi = values[i].y;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                yi = yi * (xi - values[j].x) / (values[i].x - values[j].x);
            }
        }
        result += yi;
    }
    return result;
}

std::vector<point> lagrange(int pointsNumber) {
    std::vector<point> results;
    std::vector<point> values = getPoints(function, pointsNumber);
    double interval = LENGTH / (STEPS - 1);
    for (int i = 0; i < STEPS; i++) {
        point point{};
        point.x = interval * i - END;
        point.y = lagrangeInPoint(values, point.x);
        results.push_back(point);
    }
    return results;
}

std::vector<point> lagrangeChebyshev(int pointsNumber) {
    std::vector<point> results;
    std::vector<point> values = getChebyshevPoints(function, pointsNumber);
    double interval = LENGTH / (STEPS - 1);
    for (int i = 0; i < STEPS; i++) {
        point point{};
        point.x = interval * i - END;
        point.y = lagrangeInPoint(values, point.x);
        results.push_back(point);
    }
    return results;
}

double newtonHelper(int n, double x, std::vector<point> values) {
    double result = 1;
    for (int i = 0; i < n; i++) {
        result = result * (x - values[i].x);
    }
    return result;
}

std::vector<std::vector<double>> newtonDivDiffTable(std::vector<point> values, int n) {
    std::vector<std::vector<double>> result;
    std::vector<double> empty_vec;
    empty_vec.resize(n, -1.0);
    result.resize(n, empty_vec);

    for (int i = 0; i < n; i++) {
        result[i][0] = values[i].y;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            result[j][i] = 0.0;
            result[j][i] = (result[j][i - 1] - result[j + 1][i - 1]) / (values[j].x - values[i + j].x);
        }
    }
    return result;
}


double newtonInPoint(const std::vector<point>& values, int n, double x) {
    std::vector<std::vector<double>> y = newtonDivDiffTable(values, n);
    double sum = y[0][0];
    for (int i = 1; i < n; i++) {
        sum = sum + (newtonHelper(i, x, values) * y[0][i]);
    }
    return sum;
}

std::vector<point> newton(int pointsNumber) {
    std::vector<point> results;
    std::vector<point> values = getPoints(function, pointsNumber);
    double interval = LENGTH / (STEPS - 1);
    for (int i = 0; i < STEPS; i++) {
        point point{};
        point.x = interval * i - END;
        point.y = newtonInPoint(values, pointsNumber, point.x);
        results.push_back(point);
    }
    return results;
}

std::vector<point> newtonChebyshev(int pointsNumber) {
    std::vector<point> results;
    std::vector<point> values = getChebyshevPoints(function, pointsNumber);
    double interval = LENGTH / (STEPS - 1);
    for (int i = 0; i < STEPS; i++) {
        point point{};
        point.x = interval * i - END;
        point.y = newtonInPoint(values, pointsNumber, point.x);
        results.push_back(point);
    }
    return results;
}

std::vector<std::vector<double>> hermiteDivDiffTable(std::vector<point> values, int n) {
    std::vector<std::vector<double>> result;
    std::vector<double> empty_vec;
    empty_vec.resize(2 * n, -1.0);
    result.resize(2 * n, empty_vec);

    std::vector<point> values2;

    for (int i = 0; i < n; i++) {
        values2.push_back(values[i]);
        values2.push_back(values[i]);
    }

    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < i + 1; j++) {
            if (j == 0) result[i][j] = function(values2[i].x);
            else if (j == 1 && i % 2 == 1) result[i][j] = derivative(values2[i].x);
            else {
                result[i][j] = result[i][j - 1] - result[i - 1][j - 1];
                result[i][j] = result[i][j] / (values2[i].x - values2[i - j].x);
            }
        }
    }

    return result;
}

double hermiteInPoint(std::vector<point> values, int n, double x) {
    std::vector<point> values2;

    for (int i = 0; i < n; i++) {
        values2.push_back(values[i]);
        values2.push_back(values[i]);
    }

    std::vector<std::vector<double>> y = hermiteDivDiffTable(values, n);
    double result = 0.0;
    double component = 1.0;
    for (int i = 0; i < 2 * n; i++) {
        result = result + y[i][i] * component;
        component = component * (x - values2[i].x);
    }
    return result;
}

std::vector<point> hermite(int pointsNumber) {
    std::vector<point> results;
    std::vector<point> values = getPoints(function, pointsNumber);
    double interval = LENGTH / (STEPS - 1);
    for (int i = 0; i < STEPS; i++) {
        point point;
        point.x = interval * i - END;
        point.y = hermiteInPoint(values, pointsNumber, point.x);
        results.push_back(point);
    }
    return results;
}

std::vector<point> hermiteChebyshev(int pointsNumber) {
    std::vector<point> results;
    std::vector<point> values = getChebyshevPoints(function, pointsNumber);
    double interval = LENGTH / (STEPS - 1);
    for (int i = 0; i < STEPS; i++) {
        point point;
        point.x = interval * i - END;
        point.y = hermiteInPoint(values, pointsNumber, point.x);
        results.push_back(point);
    }
    return results;
}

double lagrangeError(int n, bool chebyshev) {
    double error = 0.0;
    double interval = LENGTH / (STEPS - 1);
    std::vector<point> results;
    if (!chebyshev) {
        results = lagrange(n);
    } else {
        results = lagrangeChebyshev(n);
    }
    for (int i = 0; i < STEPS; i++) {
        error += std::abs(function(i * interval - END) - results[i].y);
    }
    return error;
}

double newtonError(int n, bool chebyshev) {
    double error = 0.0;
    double interval = LENGTH / (STEPS - 1);
    std::vector<point> results;
    if (!chebyshev) {
        results = newton(n);
    } else {
        results = newtonChebyshev(n);
    }
    for (int i = 0; i < STEPS; i++) {
        error += std::abs(function(i * interval - END) - results[i].y);
    }
    return error;
}

double hermiteError(int n, bool chebyshev) {
    double error = 0.0;
    double interval = LENGTH / (STEPS - 1);
    std::vector<point> results;
    if (!chebyshev) {
        results = hermite(n);
    } else {
        results = hermiteChebyshev(n);
    }
    for (int i = 0; i < STEPS; i++) {
        error += std::abs(function(i * interval - END) - results[i].y);
    }
    return error;
}


int main(int argc, char **argv) {
    std::cout << "preparing.";

    std::string fileExtension = ".txt";
    std::string path = "results/results";
    std::string errPath = "errors/";
    std::ofstream file;

    std::cout << ".";

    file.open(path + fileExtension);
    std::vector<point> results = getPoints(function, STEPS);
    for (point result : results) {
        file << result.x << " " << result.y << std::endl;
    }
    file.close();

    std::cout << std::endl << "calculating";

    for (int number : pointsNumber) {
        file.open(path + "L" + std::to_string(number) + fileExtension);
        results = lagrange(number);
        for (point result : results) {
            file << result.x << " " << result.y << std::endl;
        }
        file.close();
    }
    std::cout << ".";

    for (int number : pointsNumber) {
        file.open(path + "LC" + std::to_string(number) + fileExtension);
        results = lagrangeChebyshev(number);
        for (point result : results) {
            file << result.x << " " << result.y << std::endl;
        }
        file.close();
    }
    std::cout << ".";

    for (int number : pointsNumber) {
        file.open(path + "N" + std::to_string(number) + fileExtension);
        results = newton(number);
        for (point result : results) {
            file << result.x << " " << result.y << std::endl;
        }
        file.close();
    }
    std::cout << ".";

    for (int number : pointsNumber) {
        file.open(path + "NC" + std::to_string(number) + fileExtension);
        results = newtonChebyshev(number);
        for (point result : results) {
            file << result.x << " " << result.y << std::endl;
        }
        file.close();
    }
    std::cout << ".";

    for (int number : pointsNumber) {
        file.open(path + "H" + std::to_string(number) + fileExtension);
        results = hermite(number);
        for (point result : results) {
            file << result.x << " " << result.y << std::endl;
        }
        file.close();
    }
    std::cout << ".";

    for (int number : pointsNumber) {
        file.open(path + "HC" + std::to_string(number) + fileExtension);
        results = hermiteChebyshev(number);
        for (point result : results) {
            file << result.x << " " << result.y << std::endl;
        }
        file.close();
    }

    std::cout << "." << std::endl << "drawing plots";
    system("python plot.py");
    std::cout <<std::endl<< "calculating errors";

    file.open(errPath + "L" + fileExtension);
    for (int i = 2; i < 50; i++) {
        file << "Lagrange" << i << " : " << lagrangeError(i, false) << std::endl;
    }
    file.close();
    std::cout << ".";

    file.open(errPath + "LC" + fileExtension);
    for (int i = 2; i < 50; i++) {
        file << "Lagrange Ch, " << i << " : " << lagrangeError(i, true) << std::endl;
    }
    file.close();
    std::cout << ".";

    file.open(errPath + "N" + fileExtension);
    for (int i = 2; i < 50; i++) {
        file << "Newton, " << i << " : " << newtonError(i, false) << std::endl;
    }
    file.close();
    std::cout << ".";

    file.open(errPath + "NC" + fileExtension);
    for (int i = 2; i < 50; i++) {
        file << "Newton Ch, " << i << " : " << newtonError(i, true) << std::endl;
    }
    file.close();
    std::cout << ".";

    file.open(errPath + "H" + fileExtension);
    for (int i = 2; i < 50; i++) {
        file << "Hermite, " << i << " : " << hermiteError(i, false) << std::endl;
    }
    file.close();
    std::cout << ".";

    file.open(errPath + "HC" + fileExtension);
    for (int i = 2; i < 50; i++) {
        file << "Hermite Ch, " << i << " : " << hermiteError(i, true) << std::endl;
    }
    file.close();

    std::cout << "." << std::endl << "ending." << std::endl;
    return 0;
}