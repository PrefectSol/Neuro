#define DEBUG

#include <iostream>
#include <string>

#include "NetworkManager.h"
#include "Algorithm.h"

void printUsage(std::string helpWord)
{
    std::cout << "Neuro - some neural network" << std::endl;
    std::cout << "Example: <run the some module of neuro> <module args> / " << helpWord << std::endl;
}

void printHelp()
{
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "VERSION: 0.0.3\tNAME: Neuro" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Modules:" << std::endl <<
        " - GCD: 0" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

int main(int argc, const char **argv) 
{
    const std::string helpWord = "-help";

    if (argc >= 2)
    {
        if (argv[1] == helpWord)
        {
            printHelp();

            return 0;
        }

        int module;
        bool isInt = str2int(argv[1], &module);
        if (!isInt)
        {
            printUsage(helpWord);

            return 1;
        }

        uint32_t isRunModule = NetworkManager::runModule(module, argc, argv);

        #ifdef DEBUG
        std::cout << isRunModule << std::endl;
        #endif // DEBUG

        return isRunModule;
    }

    printUsage(helpWord);

    return 1;
}