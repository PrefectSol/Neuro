#include "GcdModule.h"

uint32_t runGcdModule(const Json::Value &config)
{
    const int countEpochs = config["Testing modules"]["GCD"]["number of epochs"].asInt();
    const int countIterations = config["Testing modules"]["GCD"]["number of iterations"].asInt();
    const int countData = countIterations ? countEpochs * countIterations : countEpochs;

    std::vector<std::pair<double, double>> inputData;
    std::vector<double> outputData;

    uint32_t initDataCode = initData(config, countIterations, countData, &inputData, &outputData);
    if (initDataCode != ErrorCode::success)
    {
        return initDataCode;
    }

    const double learningRate = config["Testing modules"]["GCD"]["learning rate"].asDouble();
    const double bias = config["Testing modules"]["GCD"]["bias neuron"].asDouble();
    
    const std::string feedForwardModel = config["Testing modules"]["GCD"]["network structure"].asString();
    std::vector<int> networkStruct;
    for(const auto &i : feedForwardModel) 
    {
        networkStruct.push_back(i - '0');
    }

    Network network(networkStruct, bias, learningRate);
    uint32_t runTrainCode = network.runTrainNetwork(inputData, outputData);
    if (runTrainCode != ErrorCode::success)
    {
        return runTrainCode;
    }

    return ErrorCode::success;
}

uint32_t initData(const Json::Value config, int countIterations, int countData, std::vector<std::pair<double, double>> *inputData, std::vector<double> *outputData)
{
    const int numLimit = config["Testing modules"]["GCD"]["max number of data"].asInt();
    bool isMemoryGenerating = config["Testing modules"]["GCD"]["Generating gcd data in memory"].asBool();
    if (!isMemoryGenerating)
    {
        std::string gcdDataFile = config["Testing modules"]["GCD"]["File for generating gcd data"].asString();
        uint32_t isCreateGcdData = createGcdData(countIterations, countData, numLimit, gcdDataFile);
        if (isCreateGcdData != ErrorCode::success)
        {
            return isCreateGcdData;
        }

        uint32_t isReadGcdDataFile = readGcdDataFile(gcdDataFile, inputData, outputData);
        
        return isReadGcdDataFile;
    }   

    createGcdData(countIterations, countData, numLimit, inputData, outputData);

    return ErrorCode::success;
}

uint32_t createGcdData(int countIterations, int countData, int numLimit, std::string filename)
{
    std::ofstream writer(filename);
    if(!writer.is_open())
    {
        return ErrorCode::cannotOpenFile;
    }

    srand(time(NULL));
    for(int i = 0; i < countData; i++)
    {
        int signNum1 = countIterations ? rand() % countIterations : 0;
        int signNum2= countIterations ? rand() % countIterations : 0;

        int num1 = (rand() % numLimit) * pow(-1, signNum1);
        int num2 = (rand() % numLimit) * pow(-1, signNum2);

        int gcd = getGcd(num1, num2);
        
        writer << num1 << " " << num2 << " " << gcd << '\n';
    }   

    writer.close();

    return ErrorCode::success;
}

void createGcdData(int countIterations, int countData, int numLimit, std::vector<std::pair<double, double>> *inputData, std::vector<double> *outputData)
{
    srand(time(NULL));
    for(int i = 0; i < countData; i++)
    {
        int signNum1 = countIterations ? rand() % countIterations : 0;
        int signNum2= countIterations ? rand() % countIterations : 0;

        int num1 = (rand() % numLimit) * pow(-1, signNum1);
        int num2 = (rand() % numLimit) * pow(-1, signNum2);

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