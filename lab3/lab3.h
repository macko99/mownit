#include <iostream>
#include <cmath>

struct result{
    result(double d, unsigned i) {
        value = d;
        iterations = i;
    }
    double value;
    unsigned iterations;
};

double f1 (double x);
double f2 (double x);
double f3 (double x);
double fun_chooser(double x, unsigned i);

result bisection(double start, double end, double error, unsigned fun_flag);
double derivative(double x, unsigned fun_flag);
result newton (double start, double end, unsigned iterations_max, double error, unsigned fun_flag);
result secant (double start, double end, unsigned iterations_max, double error, unsigned fun_flag);
