#include "main.hpp"

void DFT::init(std::vector<double>& input){
    this->samples = input;
    this->results.resize((unsigned) input.size());
}

void DFT::calculate(){
    auto size = (unsigned) samples.size();
    for(int i = 0; i < size; i++){
        std::complex<double> sum(0, 0);
        for(int j = 0; j < size; j++){
            sum += (std::polar(1.0, (-2 * M_PI * i * j) / size) * samples[j]);
        }
        results[i] = sum;
    }
}

std::vector<std::complex<double>> DFT::getResults(){
    return results;
}



