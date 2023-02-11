#define RELEASE

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
    std::cout << "VERSION: 0.0.7 \t NAME: Neuro" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    std::cout << "Arguments:" << std::endl <<
        "   " << _commandRun << " <path to config.json file>" << std::endl << 
        "   " << _commandCreate << " <path to config.json file>" << std::endl;

    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Testing modules:" << std::endl <<
        "   " << "1 - GCD module" << ": finding the greatest common divisor" << std::endl << 
        "   " << "2 - Parsing module" << ": getting information from the Internet by key text" << std::endl << 
        "   " << "3 - Vision module (?)" << ": object recognition" << std::endl;

    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Implementation modules: (Futures)" << std::endl <<
        "   " << "1 - Matrix module" << ": write the matrix of neural network" << std::endl << 
        "   " << "2 - Memory module" << ": save data in the neural network memory" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

void runInDebugMode()
{
    const std::string configPath = "Data/Configuration/conf.json";
    const clock_t startTimer = clock();

    createConfig(configPath);

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
    std::cout << "Testing module result: " << modulesResult[0] << std::endl;
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