#include "GcdModule.h"

uint32_t runGcdModule(int argc, const char **argv)
{
    if (argc < 3)
    {
        return ErrorCode::notEnoughArguments;
    }

    // ######################### 
    // TODO: Add CLI Parser

    int countData;
    bool isInt = str2int(argv[2], &countData);
    if (!isInt)
    {
        return ErrorCode::cannotConvertStrToInt;
    }

    std::vector<std::pair<double, double>> inputData;
    std::vector<double> outputData;
    
    uint32_t isInitData = initData(argc, argv, countData, &inputData, &outputData);
    if (isInitData != ErrorCode::success)
    {
        return isInitData;
    }
    
    // ######################### DEBUG
    // Add to CLI
    std::vector<int> networkStruct = {2, 3, 2, 3, 1};
    double nums[] = {0, 0, 0, 0, 0};
    Vector networkOffset(nums, networkStruct.size());
    int learningRate = 0.3f;
    // ######################### !DEBUG

    Network network(networkStruct, networkOffset, learningRate);
    uint32_t isRunTrain = network.runTrainNetwork(inputData, outputData);
    if (isRunTrain != ErrorCode::success)
    {
        return isRunTrain;
    }

    return ErrorCode::success;
}

uint32_t initData(int argc, const char **argv, int countData, std::vector<std::pair<double, double>> *inputData, std::vector<double> *outputData)
{
    if (argc > 3 && isPathExists(argv[3]))
    {
        uint32_t isCreateGcdData = createGcdData(countData, argv[3]);
        if (isCreateGcdData != ErrorCode::success)
        {
            return isCreateGcdData;
        }

        uint32_t isReadGcdDataFile = readGcdDataFile(argv[3], inputData, outputData);
        
        return isReadGcdDataFile;
    }   

    createGcdData(countData, inputData, outputData);

    return ErrorCode::success;
}

uint32_t createGcdData(int countData, std::string filename)
{
    std::ofstream writer(filename);
    
    if(!writer.is_open())
    {
        return ErrorCode::cannotOpenFile;
    }

    srand(time(NULL));
    for(int i = 0; i < countData; i++)
    {
        int num1 = rand() % numLimit;
        int num2 = rand() % numLimit;

        int gcd = getGcd(num1, num2);
        
        writer << num1 << " " << num2 << " " << gcd << '\n';
    }   

    writer.close();

    return ErrorCode::success;
}

void createGcdData(int countData, std::vector<std::pair<double, double>> *inputData, std::vector<double> *outputData)
{
    srand(time(NULL));
    for(int i = 0; i < countData; i++)
    {
        int num1 = rand() % numLimit;
        int num2 = rand() % numLimit;
        
        int gcd = getGcd(num1, num2);
        
        inputData->push_back(std::make_pair(num1, num2));
        outputData->push_back(gcd);
    }   
}

uint32_t readGcdDataFile(std::string filename, std::vector<std::pair<double, double>> *inputData, std::vector<double> *outputData)
{
    std::ifstream reader(filename);

    if(!reader.is_open())
    {
        return ErrorCode::cannotOpenFile;
    }

    int num1, num2, gcd;
    while(!reader.eof())
    {
        reader >> num1 >> num2 >> gcd;

        inputData->push_back(std::make_pair(num1, num2));
        outputData->push_back(gcd);
    }

    reader.close();

    return ErrorCode::success;
}