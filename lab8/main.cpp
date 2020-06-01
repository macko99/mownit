#include "main.hpp"

double calculateTime(struct timespec& timeStart, struct timespec& timeEnd){
    double timeElapsed = (timeEnd.tv_nsec - timeStart.tv_nsec) / 1000000.0;
    timeElapsed += (timeEnd.tv_sec - timeStart.tv_sec) * 1000.0;
    return timeElapsed;
}

int main(){
    std::ofstream file;
    std::vector<double> initValues {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };

    DFT dftTask1;
    dftTask1.init(initValues);
    dftTask1.calculate();
    std::vector<std::complex<double>> dftResults = dftTask1.getResults();

    std::cout << "DFT: " << std::endl;
    for(unsigned i = 0; i < dftResults.size(); i++){
        std::cout << "Sample nr " << i << ": " << dftResults[i] << std::endl;
    }
    std::cout << std::endl;


    FFT fftTask2;
    fftTask2.init(initValues);
    fftTask2.calculate();
    std::vector<std::complex<double>> fftResults = fftTask2.getResults();

    std::cout << "FFT: " << std::endl;
    for(size_t i = 0; i < fftResults.size(); i++){
        std::cout << "Sample nr " << i << ": " << fftResults[i] << std::endl;
    }
    std::cout << std::endl;


    std::vector<std::vector<double>> timeTestsTask3;
    timeTestsTask3.resize(10);
    file.open("timeData.txt");
    std::string fileText;

    for(int i = 0; i < timeTestsTask3.size(); i++){
        auto dataSize = (unsigned) (std::pow(2, i + 4));
        timeTestsTask3[i].resize(dataSize);
        for(int j = 0; j < dataSize; j++){
            timeTestsTask3[i][j] = j;
        }
    }

    for(std::vector<double> timeTest : timeTestsTask3){
        struct timespec startTime{};
        struct timespec endTime{};
        double time;

        std::cout << "Time for " << timeTest.size() << " samples:" << std::endl;
        fileText = std::to_string(timeTest.size());

        std::cout << "\tDFT: ";
        DFT dft;
        dft.init(timeTest);
        clock_gettime(CLOCK_MONOTONIC, &startTime);
        dft.calculate();
        clock_gettime(CLOCK_MONOTONIC, &endTime);
        time = calculateTime(startTime, endTime);
        std::cout << time << " ms" << std::endl;
        fileText.append("," + std::to_string(time));

        std::cout << "\tFFT: ";
        FFT fft;
        fft.init(timeTest);
        clock_gettime(CLOCK_MONOTONIC, &startTime);
        fft.calculate();
        clock_gettime(CLOCK_MONOTONIC, &endTime);
        time = calculateTime(startTime, endTime);
        std::cout << time << " ms" << std::endl;
        fileText.append("," + std::to_string(time));
        file << fileText <<std::endl;
    }
    file.close();


    //source: https://dane.imgw.pl/datastore
    // lipiec, 2019, temperatura, co 10 min
    std::ifstream is("rawData.txt");
    std::istream_iterator<double> start(is), end;
    std::vector<double> weatherData(start, end);

    FFT fftTask4;
    fftTask4.init(weatherData);
    fftTask4.calculate();
    std::vector<double> task4Results = fftTask4.getSpectrum();

    file.open("frequencyData.txt");
    for(double task4Result : task4Results){
        file << task4Result << std::endl;
    }
    system("plot.py");

    return 0;
}
