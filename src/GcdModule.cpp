#include "GcdModule.h"

uint32_t runGcdModule(const Json::Value &config)
{
    const int countEpochs = config["Creation modules"]["GCD"]["number of epochs"].asInt();
    const int countIterations = config["Creation modules"]["GCD"]["number of iterations"].asInt();
    const int countData = countIterations ? countEpochs * countIterations : countEpochs;

    std::vector<std::array<double, 2>> inputData;
    std::vector<std::array<double, 1>> outputData;

    uint32_t initDataCode = initData(config, countIterations, countData, &inputData, &outputData);
    if (initDataCode != ErrorCode::success)
    {
        return initDataCode;
    }

    const bool isAdaptive = config["Creation modules"]["GCD"]["Learning rate"]["is adaptive"].asBool();
    const double decayRate = config["Creation modules"]["GCD"]["Learning rate"]["decay rate"].asDouble();
    const double learningRate = config["Creation modules"]["GCD"]["Learning rate"]["learning rate"].asDouble();
    const double bias = config["Creation modules"]["GCD"]["bias neuron"].asDouble();
    const double targetAccuracy = config["Creation modules"]["GCD"]["target error accuracy"].asDouble();

    Functions function = (Functions)(config["Creation modules"]["GCD"]["Activation function"].asInt());

    const std::string feedForwardModel = config["Creation modules"]["GCD"]["network structure"].asString();
    std::vector<int> networkStruct;
    for(const auto &i : feedForwardModel) 
    {
        networkStruct.push_back(i - '0');
    }

    Network network(networkStruct, function , bias, learningRate, countIterations, isAdaptive, decayRate, targetAccuracy);
    uint32_t runTrainCode = network.runTrainNetwork(inputData, outputData);
    if (runTrainCode != ErrorCode::success)
    {
        return runTrainCode;
    }

    return ErrorCode::success;
}

uint32_t initData(const Json::Value config, int countIterations, int countData, std::vector<std::array<double, 2>> *inputData, std::vector<std::array<double, 1>> *outputData)
{
    const int numLimit = config["Creation modules"]["GCD"]["max number of data"].asInt();
    bool isMemoryGenerating = config["Creation modules"]["GCD"]["Generating gcd data in memory"].asBool();
    if (!isMemoryGenerating)
    {
        std::string gcdDataFile = config["Creation modules"]["GCD"]["File for generating gcd data"].asString();
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

uint32_t readGcdDataFile(std::string filename, std::vector<std::array<double, 2>> *inputData, std::vector<std::array<double, 1>> *outputData)
{
    std::ifstream reader(filename);
    if(!reader.is_open())
    {
        return ErrorCode::cannotOpenFile;
    }

    double num1, num2, gcd;
    while(!reader.eof())
    {
        reader >> num1 >> num2 >> gcd;

        inputData->push_back({num1, num2});
        outputData->push_back({gcd});
    }

    reader.close();

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
        double signNum1 = countIterations ? rand() % countIterations : 0;
        double signNum2= countIterations ? rand() % countIterations : 0;

        double num1 = (rand() % numLimit) * pow(-1, signNum1);
        double num2 = (rand() % numLimit) * pow(-1, signNum2);

        double gcd = getGcd(num1, num2);
        
        writer << num1 << " " << num2 << " " << gcd << '\n';
    }   

    writer.close();

    return ErrorCode::success;
}

void createGcdData(int countIterations, int countData, int numLimit, std::vector<std::array<double, 2>> *inputData, std::vector<std::array<double, 1>> *outputData)
{
    srand(time(NULL));
    for(int i = 0; i < countData; i++)
    {
        double signNum1 = countIterations ? rand() % countIterations : 0;
        double signNum2= countIterations ? rand() % countIterations : 0;

        double num1 = (rand() % numLimit) * pow(-1, signNum1);
        double num2 = (rand() % numLimit) * pow(-1, signNum2);

        inputData->push_back({num1, num2});
        outputData->push_back({getGcd(num1, num2)});
    }   
}
