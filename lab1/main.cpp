#include<iostream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>
#include "lab1.h"

const int N = 10000000;
const float value = 0.2345;

void error_log(float sum, int i){
    std:: ofstream results;
    results.open ("results", std::ios::out | std::ios::app);
    float absolute_err = std::abs(sum - i * value);
    float relative_err = absolute_err/(i * value)*100;
    results <<i<<","<< relative_err<<std::endl;
}
void error_count(float sum){
    float absolute_err = std::abs(sum - N * value);
    float relative_err = absolute_err/(100000 * value);
    std::cout<<"absolute error: "<<absolute_err<<" relative error: "<<relative_err<<std::endl;
}
void zad1(const std::vector<float>& array, bool log){
    float sum = 0;
    for (int i = 0; i < N; i++){
        sum+= array.at(i);
        if(log && i%25000 == 0 && i != 0){
            error_log(sum, i);
        }
    }
    if(log)
        error_log(sum, N);
    else {
        std::cout << "Suma: " << sum << std::endl;
        error_count(sum);
    }
}
void zad1_pairs (const std::vector<float>& array_initial) {
    std::vector<float> array = array_initial;
    std::vector<float> array2;
    while (array.size() != 1) {
        for (int i = 0; i < array.size(); i += 2) {
            if(i+1 < array.size()) {
                array2.push_back(array.at(i) + array.at(i + 1));
            }
            else{
                array2.push_back(array.at(i));
            }
        }
        array = array2;
        array2.clear();
    }
    std:: cout <<"Suma przy parowaniu: "<<array.at(0) <<std::endl;
    error_count(array.at(0));
}
float zad2(const std::vector<float>& array, bool result){
    float sum = 0.0, err = 0.0, y, temp;
    for (float element : array){
        y = element - err;
        temp = sum + y;
        err = (temp - sum) - y;
        sum = temp;
    }
    if(result) {
        std::cout << "Suma Kahan: " << sum << std::endl;
        error_count(sum);
    }
    return sum;
}

void zad3_float (int n){
    float denominator = 4.0, sum = 0.0;
    float denominator_rev = pow(2, n+1), sum_rev = 0.0;
    for (int i = 0; i < n; i++){
        sum += 1.0/denominator;
        sum_rev += 1.0/denominator_rev;
        denominator *= 2;
        denominator_rev /= 2;
    }
    std:: cout <<std::setprecision(32) <<"Suma w przod("<<n<<"): "<<sum <<" suma w tyl: "<<sum_rev <<std::endl;
}
void zad3_double (int n){
    double denominator = 4.0, sum = 0.0;
    double denominator_rev = pow(2, n+1), sum_rev = 0.0;
    for (int i = 0; i < n; i++){
        sum += 1.0/denominator;
        sum_rev += 1.0/denominator_rev;
        denominator *= 2;
        denominator_rev /= 2;
    }
    std:: cout <<std::setprecision(32) <<"Suma w przod (double)("<<n<<"): "<<sum <<" suma w tyl (double): "<<sum_rev <<std::endl;
}
void zad3_kahan (int n){
    std::vector<float> array;
    float denominator = 4.0;
    for (int i = 0; i < n; i++){
        array.push_back(1.0/denominator);
        denominator *= 2;
    }
    std:: cout <<std::setprecision(32) <<"Suma kahan("<<n<<"): "<<zad2(array, false) <<std::endl;
}

void zad4(){
    double epsilon = 0.5;
    while ((1+epsilon) != 1){
        epsilon /=2;
    }
    std:: cout  << std::setprecision(-1) <<std::endl << "epsilon: "<<epsilon <<std::endl;
}

int main()
{
    clock_t start, end;
    double time_taken;

    std::vector<float> array;
    for (int i = 0; i < N; i++){
        array.push_back(value);
    }

    start = clock();
    zad1(array, false);
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken standard ver: " << time_taken << " sec " << std::endl <<std::endl;

    zad1(array, true);

    start = clock();
    zad1_pairs(array);
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken recursive ver: " << time_taken << " sec " << std::endl <<std::endl;

    start = clock();
    zad2(array, true);
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken Kahan ver: " << time_taken << " sec " << std::endl <<std::endl;

    zad3_float(50);
    zad3_float(100);
    zad3_float(200);
    zad3_float(500);
    zad3_float(800);
    zad3_double(50);
    zad3_double(100);
    zad3_double(200);
    zad3_double(500);
    zad3_double(800);
    zad3_kahan(50);
    zad3_kahan(100);
    zad3_kahan(200);
    zad3_kahan(500);
    zad3_kahan(800);


    zad4();

    return 0;
}
