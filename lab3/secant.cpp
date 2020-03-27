#include "lab3.h"
#include <iostream>
#include <cmath>

result secant (double start, double end, unsigned iterations_max, double error, unsigned fun_flag){
    unsigned iterations = iterations_max;
    double value1 = fun_chooser(start, fun_flag);
    double value2 = fun_chooser(end, fun_flag);
    double val_of_arg, arg = 0.0, old_val = 0.0;

    while(--iterations){
        arg = (value1 * end - value2 * start) / (value1 - value2);
        val_of_arg = fun_chooser(arg, fun_flag);

        if(std::abs(val_of_arg - old_val) < error || std::abs(arg - end) < error)
            break;

        start = end;
        end = arg;
        value1 = value2;
        value2 = val_of_arg;
    }

    return *new struct result(arg, iterations_max - iterations);
}