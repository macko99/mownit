#include "main.hpp"

void FFT::init(std::vector<double>& input){
    this->results.resize((unsigned) input.size());

    for(unsigned i = 0; i < input.size(); i++){
        results[i] = std::complex<double>(input[i], 0);
    }
}

void FFT::calculate(){
    fft(results);
}

void FFT::fft(std::vector<std::complex<double>>& values){
    const unsigned N = values.size();
    if (N <= 1)
        return;

    std::vector<std::complex<double>> even, odd;
    for(int i = 0; i < N; i++){
        if(i % 2 == 0)
            even.push_back(values[i]);
        else
            odd.push_back(values[i]);
    }

    fft(even);
    fft(odd);

    for (unsigned i = 0; i < N/2; i++){
        std::complex<double> tmp = std::polar(1.0, -2 * M_PI * i / N) * odd[i];
        values[i] = even[i] + tmp;
        values[i + N / 2] = even[i] - tmp;
    }
}

std::vector<std::complex<double>> FFT::getResults(){
    return results;
}

std::vector<double> FFT::getSpectrum(){
    std::vector<double> spectrum;
    spectrum.resize(results.size());
    for(int i = 0; i < spectrum.size(); i++){
        spectrum[i] = abs(results[i]);
    }
    return spectrum;
}

