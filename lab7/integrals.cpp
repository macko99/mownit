#include "integrals.hpp"

double integrals::rectangleMethod(double start, double end, int density, const std::function <double(double)>& function){
    double result = 0;
    double interval = (end - start) / density;
    for(int i = 1; i <= density; i++){
        result += (interval * function(start + interval * i));
    }
    return result;
}

double integrals::trapeziumMethod(double start, double end, int density, const std::function <double(double)>& function){
    double result = 0;
    double interval = (end - start) / density;
    for(int i = 0; i < density; i++){
        double fx0 = function(start + interval * i);
        double fx1 = function(start + interval * (i + 1));
        result += ((fx0 + fx1) * interval / 2);
    }
    return result;
}

double integrals::simpsonMethod(double start, double end, int density, const std::function <double(double)>& function){
    double result = 0;
    double interval = (end - start) / density;
    for(int i = 0; i < density; i++){
        double fx0 = function(start + interval * i);
        double fx1 = function(start + interval * (i + 0.5));
        double fx2 = function(start + interval * (i + 1));
        result += ((interval / 6) * (fx0 + 4 * fx1 + fx2));
    }
    return result;
}

double integrals::monteCarloMethod(double start, double end, int density, const std::function <double(double)>& function){
    double totalArea = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(start, end);
    for(int i = 0; i < density; i++){
        double x0 = dis(gen);
        double tmpArea = function(x0) * (end - start);
        totalArea += tmpArea;
    }
    return totalArea / density;
}

double integrals::monteCarloPI(int samplesNumber){
    int innerSamples = 0;
    double radius = 1.0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, radius);
    for(int i = 0; i < samplesNumber; i++){
        double x = dis(gen);
        double y = dis(gen);
        if(sqrt(x*x + y*y) <= radius){
            innerSamples++;
        }
    }
    return 4.0 * innerSamples / samplesNumber;
}