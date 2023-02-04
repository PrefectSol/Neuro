#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <cmath>
#include <filesystem>

namespace ActivationFunctions
{
    double linear(double x, int k = 2);

    double semiLinear(double x, int k = 2);

    double sigmoid(double x);

    double hyperbolicTangent(double x);

    double exponential(double x);
    
    double quadratic(double x);

    double sign(double x);
};

bool isPathExists(std::string filename);

bool str2int(std::string str, int *num);

double getRandomDouble();

int getGcd(int a, int b);

#endif // !ALGORITHM