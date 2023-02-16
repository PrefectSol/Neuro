#define TEMPLATE_PROJECT
#define DEBUG_FALSE

#define INDENT_3 "   "
#define INDENT_6 "      "

#include <json/json.h>

#include "NetworkManager.h"
#include "Algorithm.h"

const std::string _commandHelp = "help";
const std::string _commandRun = "run";
const std::string _commandCreate = "create";

void printUsage()
{
    std::cout << "Neuro - CLI for training and implementation of new modules in neural networks." << std::endl;
    std::cout << "Example: ./Neuro [arguments] | " << _commandHelp << std::endl;
}

void printHelp()
{
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "VERSION: 0.2 \t NAME: Neuro" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    std::cout << "Arguments:" << std::endl <<
        INDENT_3 << _commandRun << " <path to config.json file>" << std::endl << 
        INDENT_3 << _commandCreate << " <path to config.json file>" << std::endl;

    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Run Creation Modules:" << std::endl <<
        INDENT_3 << "1 - GCD module" << ": finding the greatest common divisor (Module for testing)" << std::endl << 
        INDENT_3 << "2 - Parsing module" << ": getting information from the Internet by key text" << std::endl << 
        INDENT_3 << "3 - Vision module (?)" << ": object recognition" << std::endl;
    std::cout << std::endl << INDENT_3 << "Activation/Derivative function:" << std::endl <<
        INDENT_6 << "0 - linear" << std::endl << 
        INDENT_6 << "1 - semiLinear" << std::endl << 
        INDENT_6 << "2 - sigmoid" << std::endl << 
        INDENT_6 << "3 - hyperbolicTangent" << std::endl << 
        INDENT_6 << "4 - hyperbolic" << std::endl << 
        INDENT_6 << "5 - exponential" << std::endl << 
        INDENT_6 << "6 - quadratic" << std::endl << 
        INDENT_6 << "7 - sign" << std::endl << 
        INDENT_6 << "8 - single" << std::endl;

    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Run Implementation Modules: (Futures)" << std::endl <<
        INDENT_3 << "1 - Matrix module" << ": write the matrix of neural network" << std::endl << 
        INDENT_3 << "2 - Memory module" << ": save data in the neural network memory" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

void runInDebugMode()
{
    const std::string configPath = "Data/Configuration/conf.json";
    const clock_t startTimer = clock();

    // createConfig(configPath);

    // printHelp();
    // printUsage();

    std::ifstream jsonFile(configPath, std::ifstream::binary);
    Json::Value config;
    jsonFile >> config;
    jsonFile.close();

    ErrorCode modulesResult[2];
    uint32_t debugRunCode = NetworkManager::runModule(config, modulesResult);

    const clock_t finishTimer = clock();

    std::cout << "Execution time: " << (finishTimer - startTimer) / (double)CLOCKS_PER_SEC << std::endl;
    std::cout << "Common result: " << debugRunCode << std::endl;
    std::cout << "Creation module result: " << modulesResult[0] << std::endl;
    std::cout << "Implementation module result: " << modulesResult[1] << std::endl;
}

int main(int argc, char **argv)  
{
#ifdef DEBUG
    runInDebugMode();
    
    return 2;
#endif // !DEBUG

    if (argc == 2 && argv[1] == _commandHelp)
    {
        printHelp();

        return 0;
    }

    if (argc == 3)
    {   
        if (argv[1] == _commandRun && isFileExists(argv[2], ".json"))
        {
            std::ifstream jsonFile(argv[2], std::ifstream::binary);
            Json::Value config;
            jsonFile >> config;
            jsonFile.close();

            uint32_t runCode = NetworkManager::runModule(config);

            return runCode;
        }

        if (argv[1] == _commandCreate && isPathExists(argv[2]) && isCorrectExtension(argv[2], ".json"))
        {
            createConfig(argv[2]);

            return 0;
        }
    }

    printUsage();

    return 1;
}