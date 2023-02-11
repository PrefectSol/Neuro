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

bool isCorrectExtension(std::string filename, std::string extension)
{
    std::filesystem::path file = filename;

    return file.extension() == extension;
 }

bool isFileExists(std::string filename, std::string extension)
{

    std::filesystem::path file = filename;
    bool isExists = std::filesystem::exists(filename) && file.extension() == extension;

    return isExists;
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
    a = abs(a);
    b = abs(b);

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

void createConfig(std::string path)
{
    Json::Value config;

    config["Testing modules"]["Run the module"] = 1;

    config["Testing modules"]["GCD"]["number of epochs"] = 500000;
    config["Testing modules"]["GCD"]["number of iterations"] = 2; // negative and positive numbers = (-1)^n

    config["Testing modules"]["GCD"]["Generating gcd data in memory"] = true; // Memory(true) | File(false)
    config["Testing modules"]["GCD"]["File for generating gcd data"] = "Data/GCD/gcd.txt"; // If File(false)
    config["Testing modules"]["GCD"]["max number of data"] = 10000;
    
    // Feed Forward Structure
    config["Testing modules"]["GCD"]["network structure"] = "23231"; // input | ... hidden ... | output. Num - count of neurons on layer
    config["Testing modules"]["GCD"]["bios neuron"] = 0.0;
    config["Testing modules"]["GCD"]["learning rate"] = 0.3f;

    config["Testing modules"]["Parsing"]["key text"] = "some text";

    config["Implementation modules"]["Run the module"] = 0;
    
    std::ofstream jsonFile(path, std::ios::binary);
    jsonFile << config;

    jsonFile.close();
}
