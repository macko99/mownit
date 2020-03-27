#include <iostream>
#include <cmath>
#include "lab3.h"

double f1 (double x){
    return (cos(x)*cosh(x)-1);
}
double f2 (double x){
    return ((1/x) - tan(x));
}
double f3 (double x){
    return (pow(2.0,-x) + exp(x) + 2*cos(x) - 6);
}

double fun_chooser(double x, unsigned i){
    if (i == 1)
        return f1(x);
    else if (i == 2)
        return f2(x);
    else
        return f3(x);
}

int main() {
    result results = bisection(1.5*M_PI, 2*M_PI, pow(10.0,-13), 1);
    std::cout <<results.value<<" " <<results.iterations<<std::endl;
    results = bisection(0, 0.5*M_PI, pow(10.0,-33), 2);
    std::cout <<results.value<<" " <<results.iterations<<std::endl;
    results = bisection(1, 3, pow(10.0,-33), 3);
    std::cout <<results.value<<" " <<results.iterations<<std::endl<<std::endl;

    results = newton(1.5*M_PI, 2*M_PI, 100, pow(10.0,-33), 1);
    std::cout <<results.value<<" " <<results.iterations<<std::endl;
    results = newton(0, 0.5*M_PI, 100, pow(10.0,-33), 2);
    std::cout <<results.value<<" " <<results.iterations<<std::endl;
    results = newton(1, 3, 100, pow(10.0,-33), 3);
    std::cout <<results.value<<" " <<results.iterations<<std::endl<<std::endl;

    results = secant(1.5*M_PI, 2*M_PI, 100, pow(10.0,-33), 1);
    std::cout <<results.value<<" " <<results.iterations<<std::endl;
    results = secant(0., 0.5*M_PI, 100, pow(10.0,-33), 2);
    std::cout <<results.value<<" " <<results.iterations<<std::endl;
    results = secant(1, 3, 100, pow(10.0,-33), 3);
    std::cout <<results.value<<" " <<results.iterations<<std::endl<<std::endl;
    return 0;
}
