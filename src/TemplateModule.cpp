#include "../include/Modules/TemplateModule.h"

uint32_t runTemplateModule(const Json::Value &config)
{
    const int epochsCount = config["Creation modules"]["Template"]["Data"]["number of epochs"].asInt();
    const int iterationsCount = config["Creation modules"]["Template"]["Data"]["number of iterations"].asInt();
    
    std::vector<std::array<double, 1>> inputData;
    std::vector<std::array<double, 1>> outputData;

    const bool isPersonalData = config["Creation modules"]["Template"]["Data"]["generate data"].asBool();
    if (isPersonalData)
    {
        uint32_t isCreateDataCode = createPersonalData(&inputData, &outputData, epochsCount, iterationsCount);
        if (isCreateDataCode != ErrorCode::success)
        {
            return isCreateDataCode;
        }
    }
    else 
    {
        const std::string inputDataPath = config["Creation modules"]["Template"]["Data"]["input data"].asString();
        const std::string outputDataPath = config["Creation modules"]["Template"]["Data"]["output data"].asString();

        uint32_t isReadInputCode = readFile(inputDataPath, &inputData);
        if (isReadInputCode != ErrorCode::success)
        {
            return isReadInputCode;
        }

        uint32_t isReadOutputCode = readFile(outputDataPath, &outputData);
        if (isReadOutputCode != ErrorCode::success)
        {
            return isReadOutputCode;
        }
    }

    const bool isAdaptive = config["Creation modules"]["GCD"]["Learning rate"]["is adaptive"].asBool();
    const double decayRate = config["Creation modules"]["GCD"]["Learning rate"]["decay rate"].asDouble();
    const double learningRate = config["Creation modules"]["GCD"]["Learning rate"]["learning rate"].asDouble();
    const double bias = config["Creation modules"]["GCD"]["bias neuron"].asDouble();

    Functions function = (Functions)(config["Creation modules"]["GCD"]["Activation function"].asInt());

    const std::string feedForwardModel = config["Creation modules"]["GCD"]["network structure"].asString();
    std::vector<int> networkStruct;
    for(const auto &i : feedForwardModel) 
    {
        networkStruct.push_back(i - '0');
    }

    Network network(networkStruct, function, bias, learningRate, epochsCount, isAdaptive, decayRate);
    uint32_t runTrainCode = network.runTrainNetwork(inputData, outputData);
    if (runTrainCode != ErrorCode::success)
    {
        return runTrainCode;
    }

    return ErrorCode::success;
}

uint32_t createPersonalData(std::vector<std::array<double, 1>> *inputData, std::vector<std::array<double, 1>> *outputData, int countEpochs, int countIterations)
{
    // Write your personal algorithm for generate data.
    // For view all available error check AudioLog.h and return ErrorCode::error

    return ErrorCode::success;
}

uint32_t readFile(std::string filename, std::vector<std::array<double, 1>> *data)
{
    std::ifstream reader(filename);
    if(!reader.is_open())
    {
        return ErrorCode::cannotOpenFile;
    }

    double num;
    while(!reader.eof())
    {
        reader >> num;
        data->push_back({num});
    }

    reader.close();

    return ErrorCode::success;
}