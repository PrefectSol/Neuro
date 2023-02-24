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
    return hyperbolicSin(x) / hyperbolicCos(x);
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



double DerivativeFunctions::linear(double x)
{
    return 2;
}

double DerivativeFunctions::semiLinear(double x)
{
    return x > 0 ? 2 : 0;
}

double DerivativeFunctions::sigmoid(double x)
{
    return ActivationFunctions::sigmoid(x) * (1 - ActivationFunctions::sigmoid(x));
}

double DerivativeFunctions::hyperbolicTangent(double x)
{
    return 1 / pow(hyperbolicCos(x), 2);
}

double DerivativeFunctions::hyperbolic(double x)
{
    return -1.l / pow(x, 2);
}

double DerivativeFunctions::exponential(double x)
{
    return pow(M_E, -x);
}

double DerivativeFunctions::quadratic(double x)
{
    return 2 * x;
}

double DerivativeFunctions::sign(double x)
{
    return 0;
}

double DerivativeFunctions::single(double x)
{
    return 1;
}



double hyperbolicCos(double x)
{
    (pow(M_E, x) + pow(M_E, -x)) / 2;
}

double hyperbolicSin(double x)
{
    (pow(M_E, x) - pow(M_E, -x)) / 2;
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

bool isFileExists(std::string filename)
{
    std::filesystem::path file = filename;
    bool isExists = std::filesystem::exists(filename);

    return isExists;
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

double getGcd(int a, int b)
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

void createStream(std::string path)
{
    // create...
}

void createConfig(std::string path)
{
    Json::Value config;

    //######################################
    config["Creation modules"]["Run the module"] = 3; // Choose module
    //######################################



    //######################################
    config["Creation modules"]["GCD"]["Activation function"] = 2;

    config["Creation modules"]["GCD"]["number of epochs"] = 500000;
    config["Creation modules"]["GCD"]["number of iterations"] = 2; // negative and positive numbers = (-1)^n

    config["Creation modules"]["GCD"]["Generating gcd data in memory"] = true; // Memory(true) | File(false)
    config["Creation modules"]["GCD"]["File for generating gcd data"] = "Data/GcdModule/gcd.txt"; // If File(false)
    config["Creation modules"]["GCD"]["max number of data"] = 100000000;
    
    config["Creation modules"]["GCD"]["type of network structure"] = "FFS"; // Only Feed Forward Structure
    config["Creation modules"]["GCD"]["network structure"] = "23245321"; // input_0 | hidden_1 ... hidden_N-1 | output_N. Count of neurons on layer
    config["Creation modules"]["GCD"]["target error accuracy"] = 0.0001f; // Stop training if (error <= value)
    config["Creation modules"]["GCD"]["bias neuron"] = 1.0f; // Value of layer sum

    config["Creation modules"]["GCD"]["Learning rate"]["is adaptive"] = true;
    config["Creation modules"]["GCD"]["Learning rate"]["learning rate"] = 0.1f;
    config["Creation modules"]["GCD"]["Learning rate"]["decay rate"] = 0.5f; // if ["is adaptive"] is true
    //######################################



    //######################################
    // For auto generating personal data check createPersonalData() in TemplateModule.cpp. If ["generate data"] = true;
    config["Creation modules"]["Template"]["Data"]["generate data"] = true;

    // Paths to is ready data for training NN
    config["Creation modules"]["Template"]["Data"]["input data"] = "Data/TemplateModule/inputData.txt"; // if ["generate data"] = false;
    config["Creation modules"]["Template"]["Data"]["output data"] = "Data/TemplateModule/outputData.txt"; // if ["generate data"] = false;
    
    config["Creation modules"]["Template"]["Data"]["number of epochs"] = 1000000;
    config["Creation modules"]["Template"]["Data"]["number of iterations"] = 1;
    //######################################



    //######################################
    config["Creation modules"]["Parsing"]["search text"] = "population of the world";
    //######################################



    //######################################
    config["Implementation modules"]["Run the module"] = 0;
    //######################################



    std::ofstream jsonFile(path, std::ios::binary);
    jsonFile << config;

    jsonFile.close();
}
