#include "Network.h"

Network::Network(const std::vector<int> &networkStruct, Vector &networkOffset, int learningRate)
    : learningRate(learningRate) 
{
    network.neuronLayersCount = networkStruct.size();
    network.neuronLayers = new Vector*[network.neuronLayersCount];
    for(int i = 0; i < network.neuronLayersCount; i++)
    {
        network.neuronLayers[i] = new Vector(networkStruct[i]);
    }

    network.weightsLayersCount = networkStruct.size() - 1;
    network.weightsLayers = new Matrix*[network.weightsLayersCount];
    for(int i = 0; i < network.weightsLayersCount; i++)
    {
        network.weightsLayers[i] = new Matrix(networkStruct[i + 1], networkStruct[i]);
    }

    network.offsetLayers = &networkOffset;
}

Network::~Network()
{
    for(int i = 0; i < network.neuronLayersCount; i++)
    {
        delete network.neuronLayers[i];
    }
    delete[] network.neuronLayers;

    for(int i = 0; i < network.weightsLayersCount; i++)
    {
        delete network.weightsLayers[i];
    }
    delete[] network.weightsLayers;
}

uint32_t Network::runTrainNetwork(const std::vector<std::pair<double, double>> &inputData, const std::vector<double> &outputData)
{
    for(int i = 0; i < inputData.size(); i++)
    {
        uint32_t isPropagateForward = propagateForward(inputData[i]);
        if (isPropagateForward != ErrorCode::success)
        {
            return isPropagateForward;
        }
    }

    return ErrorCode::success;
}

uint32_t Network::propagateForward(const std::pair<double, double> &input)
{
    double inputLayer[2] = {input.first, input.second};
    uint32_t isSetInput = network.neuronLayers[0]->setSizedData(inputLayer, 2);
    if (isSetInput != ErrorCode::success)
    {
        return isSetInput;
    }

    double (*activationFunc)(double x);
    activationFunc = ActivationFunctions::sigmoid;

    Vector matrix2vectorResult(network.neuronLayersCount);
    Vector vector2vectorResult(network.neuronLayersCount);
    Vector newNeuronLayer(network.neuronLayersCount);

    for(int i = 1; i < network.weightsLayersCount; i++)
    {
        BasicOperations::multiplyMatrix2Vector(*network.weightsLayers[i], *network.neuronLayers[i], &matrix2vectorResult);
        BasicOperations::sumVector2Vector(matrix2vectorResult, network.offsetLayers[i], &vector2vectorResult);
        BasicOperations::activateNeuronLayer(activationFunc, vector2vectorResult, &newNeuronLayer);

        network.neuronLayers[i]->setSizedData(newNeuronLayer.getAllElements(), network.neuronLayersCount);
    }

    return ErrorCode::success;
}
