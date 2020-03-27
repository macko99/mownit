#include "lab3.h"
#include <iostream>
#include <cmath>

double derivative(double x, unsigned fun_flag){
    double derivative = fun_chooser(x, fun_flag);
    double tmp = fun_chooser(x, fun_flag) - 1;
    double h = 1.0;

    while (derivative != tmp){
        tmp = derivative;
        derivative = (fun_chooser(x + h, fun_flag) - fun_chooser(x - h, fun_flag)) / (2 * h);
        h /= 2.0;
    }
    return derivative;
}

result newton (double start, double end, unsigned iterations_max, double error, unsigned fun_flag){
    unsigned iterations = iterations_max;
    double arg = (end + start) / 2;
    double old_value = 0.0;

    while(--iterations){
        double new_value = fun_chooser(arg, fun_flag) / derivative(arg, fun_flag);
        if (std::abs(old_value - new_value) <= error)
            break;
        old_value = new_value;
        arg = arg - new_value;
    }

    return *new result(arg, iterations_max - iterations);
}