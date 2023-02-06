#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <cmath>
#include <filesystem>

namespace ActivationFunctions
{
    double linear(double x);

    double semiLinear(double x);

    double sigmoid(double x);

    double hyperbolicTangent(double x);

    double exponential(double x);
    
    double quadratic(double x);

    double sign(double x);

    double single(double x);
};

bool isPathExists(std::string filename);

bool str2int(std::string str, int *num);

double getRandomDouble();

int getGcd(int a, int b);

void initArray(double *array, int size, double value);

#endif // !ALGORITHM