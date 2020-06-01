#ifndef DFT_FFT
#define DFT_FFT

#include <complex>
#include <cmath>
#include <iostream>
#include <vector>
#include <pthread_time.h>
#include <fstream>
#include <iterator>

class DFT {
private:
    std::vector<double> samples;
    std::vector<std::complex<double>> results;

public:
    void init(std::vector<double>& input);
    void calculate();
    std::vector<std::complex<double>> getResults();
};

class FFT {
private:
    std::vector<std::complex<double>> results;
    void fft(std::vector<std::complex<double>>& values);

public:
    void init(std::vector<double>& input);
    void calculate();
    std::vector<std::complex<double>> getResults();
    std::vector<double> getSpectrum();
};

#endif