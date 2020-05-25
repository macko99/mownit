#include "integrals.hpp"
#define START 0
#define END 10
#define DENSITY (END-START)

int main(){
    integrals integrals;
    std::string fileExtension = ".txt";
    std::string path = "results/";
    std::ofstream file;

    std::function <double(double)> linear = [](double x) { return 4*x; };
    std::function <double(double)> quadratic = [](double x) { return 4*x*x - 8*x + 4; };
    std::function <double(double)> cubic = [](double x) { return 2*x*x*x - 6*x*x + 3*x - 10; };
    std::function <double(double)> exponential = [](double x) { return std::pow(M_E, x); };
    std::function <double(double)> sinusoidal = [](double x) { return sin(x)*cos(x); };


    file.open(path + "linear_rectangle" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.rectangleMethod(START, END, DENSITY*i, linear)<<std::endl;
    file.close();

    file.open(path + "linear_trapezium" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.trapeziumMethod(START, END, DENSITY*i, linear)<<std::endl;
    file.close();

    file.open(path + "linear_simpson" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.simpsonMethod(START, END, DENSITY*i, linear)<<std::endl;
    file.close();

    file.open(path + "linear_monteCarlo" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.monteCarloMethod(START, END, DENSITY*i, linear)<<std::endl;
    file.close();


    file.open(path + "quadratic_rectangle" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.rectangleMethod(START, END, DENSITY*i, quadratic)<<std::endl;
    file.close();

    file.open(path + "quadratic_trapezium" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.trapeziumMethod(START, END, DENSITY*i, quadratic)<<std::endl;
    file.close();

    file.open(path + "quadratic_simpson" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.simpsonMethod(START, END, DENSITY*i, quadratic)<<std::endl;
    file.close();

    file.open(path + "quadratic_monteCarlo" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.monteCarloMethod(START, END, DENSITY*i, quadratic)<<std::endl;
    file.close();


    file.open(path + "cubic_rectangle" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.rectangleMethod(START, END, DENSITY*i, cubic)<<std::endl;
    file.close();

    file.open(path + "cubic_trapezium" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.trapeziumMethod(START, END, DENSITY*i, cubic)<<std::endl;
    file.close();

    file.open(path + "cubic_simpson" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.simpsonMethod(START, END, DENSITY*i, cubic)<<std::endl;
    file.close();

    file.open(path + "cubic_monteCarlo" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.monteCarloMethod(START, END, DENSITY*i, cubic)<<std::endl;
    file.close();


    file.open(path + "exponential_rectangle" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.rectangleMethod(START, END, DENSITY*i, exponential)<<std::endl;
    file.close();

    file.open(path + "exponential_trapezium" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.trapeziumMethod(START, END, DENSITY*i, exponential)<<std::endl;
    file.close();

    file.open(path + "exponential_simpson" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.simpsonMethod(START, END, DENSITY*i, exponential)<<std::endl;
    file.close();

    file.open(path + "exponential_monteCarlo" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.monteCarloMethod(START, END, DENSITY*i, exponential)<<std::endl;
    file.close();


    file.open(path + "sinusoidal_rectangle" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.rectangleMethod(START, END, DENSITY*i, sinusoidal)<<std::endl;
    file.close();

    file.open(path + "sinusoidal_trapezium" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.trapeziumMethod(START, END, DENSITY*i, sinusoidal)<<std::endl;
    file.close();

    file.open(path + "sinusoidal_simpson" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.simpsonMethod(START, END, DENSITY*i, sinusoidal)<<std::endl;
    file.close();

    file.open(path + "sinusoidal_monteCarlo" + fileExtension);
    for( int i = 1; i <= 20; i++)
        file << DENSITY*i << " " << integrals.monteCarloMethod(START, END, DENSITY*i, sinusoidal)<<std::endl;
    file.close();


    file.open(path + "PI_monteCarlo" + fileExtension);
    for( int i = 100; i <= 20000; i+=100)
        file << i << " " << integrals.monteCarloPI(i)<<std::endl;
    file.close();

    system("python plot.py");

}