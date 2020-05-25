#ifndef INTEGRALS_HPP
#define INTEGRALS_HPP

#include <iostream>
#include <functional>
#include <random>
#include <fstream>

class integrals {
private:

public:
    static double rectangleMethod(double start, double end, int density, const std::function <double(double)>& function);
    static double trapeziumMethod(double start, double end, int density, const std::function <double(double)>& function);
    static double simpsonMethod(double start, double end, int density, const std::function <double(double)>& function);
    static double monteCarloMethod(double start, double end, int density, const std::function <double(double)>& function);
    static double monteCarloPI(int samplesNumber);
};

#endif