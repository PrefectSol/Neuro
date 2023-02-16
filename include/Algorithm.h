#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <cmath>
#include <filesystem>
#include <fstream>

#include <json/json.h>

enum Functions
{
    linear = 0,
    semiLinear,
    sigmoid,
    hyperbolicTangent,
    hyperbolic,
    exponential,
    quadratic,
    sign,
    single
};

namespace ActivationFunctions
{
    double linear(double x);

    double semiLinear(double x);

    double sigmoid(double x);

    double hyperbolicTangent(double x);

    double hyperbolic(double x);

    double exponential(double x);
    
    double quadratic(double x);

    double sign(double x);

    double single(double x);
};

namespace DerivativeFunctions
{
    double linear(double x);

    double semiLinear(double x);

    double sigmoid(double x);

    double hyperbolicTangent(double x);

    double hyperbolic(double x);

    double exponential(double x);
    
    double quadratic(double x);

    double sign(double x);

    double single(double x);
}

double hyperbolicCos(double x);

double hyperbolicSin(double x);

double getRandomDouble();

double getGcd(int a, int b);

bool isPathExists(std::string filename);

bool isCorrectExtension(std::string filename, std::string extension);

bool isFileExists(std::string filename, std::string extension);

bool str2int(std::string str, int *num);

void initArray(double *array, int size, double value);

void createConfig(std::string path);

#endif // !ALGORITHM