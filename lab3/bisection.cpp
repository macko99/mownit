#include "lab3.h"
#include <iostream>
#include <cmath>

result bisection(double start, double end, double error, unsigned fun_flag){
    unsigned iterations = 0;
    double middle = 0.0;

    if(fun_chooser(start, fun_flag) * fun_chooser(end, fun_flag) >= 0){
        std::cout<<"wrong parameters"<<std::endl;
        exit(-1);
    }

    while((end - start) >= error){
        iterations++;
        middle = (start + end)/2;
        if (std::abs(fun_chooser(middle, fun_flag)) <= error)
            break;
        else if(fun_chooser(middle, fun_flag) * fun_chooser(start, fun_flag) < 0)
            end = middle;
        else
            start = middle;
    }

    return *new result(middle, iterations);
}