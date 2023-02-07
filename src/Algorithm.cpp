#include "Algorithm.h"

double ActivationFunctions::linear(double x)
{
    return 2 * x;
}

double ActivationFunctions::semiLinear(double x)
{
    return x > 0 ? 2 * x : 0;
}

double ActivationFunctions::sigmoid(double x)
{
    return 1 / (1 + pow(M_E, -x));
}

double ActivationFunctions::hyperbolicTangent(double x)
{
    return 1 / (pow(M_E, x) + pow(M_E, -x));
}

double ActivationFunctions::hyperbolic(double x)
{
    return 1.l / x;
}

double ActivationFunctions::exponential(double x)
{
    return pow(M_E, -x);
}

double ActivationFunctions::quadratic(double x)
{
    return pow(x, 2);
}

double ActivationFunctions::sign(double x)
{
    return x > 0 ? 1 : -1;
}

double ActivationFunctions::single(double x)
{
    return x;
}

bool isPathExists(std::string filename)
{
    std::filesystem::path directory = filename;
    directory.remove_filename();

    bool isDirectoryExists = std::filesystem::exists(directory);

    return isDirectoryExists;
}

bool str2int(std::string str, int *num)
{
    try
    {
        *num = std::stoi(str);
    }
    catch(...)
    {
        return 0;
    }

    return 1;
}

double getRandomDouble()
{
    return (double)(RAND_MAX) / (double)(rand());
}

int getGcd(int a, int b)
{
    while (a && b)
    {
        a > b ? a %= b : b %= a;
    }
    
    return a + b; 
}

void initArray(double *array, int size, double value)
{
    for(int i = 0; i < size; i++)
    {
        array[i] = value;
    }
}
