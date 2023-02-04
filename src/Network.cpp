#include "Network.h"

Network::Network(const std::vector<int> &networkStruct, Matrix *networkOffset, int learningRate)
    : learningRate(learningRate) 
{
    if (networkOffset->getCols() != 1)
    {
        throw std::runtime_error("Invalid network offset.");
    }

    try
    {
        network.neuronLayersCount = networkStruct.size();
        network.neuronLayers = new Matrix*[network.neuronLayersCount];
        for(int i = 0; i < network.neuronLayersCount; i++)
        {
            network.neuronLayers[i] = new Matrix(networkStruct[i], 1, false);
        }

        network.weightsLayersCount = networkStruct.size() - 1;
        network.weightsLayers = new Matrix*[network.weightsLayersCount];
        for(int i = 0; i < network.weightsLayersCount; i++)
        {
            network.weightsLayers[i] = new Matrix(networkStruct[i + 1], networkStruct[i]);
        }
    }
    catch(...)
    {
        throw std::runtime_error("Cannot create the matrix.");
    }

    if (!networkOffset->isZeroMatrix())
    {
        network.offsetLayersCount = networkOffset->getSize();
        network.offsetLayers = &networkOffset;
    }
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

void Network::runTrainNetwork(std::vector<std::pair<int, int>> &inputData, std::vector<int> &outputData)
{

}

void Network::propagateForward(const std::pair<int, int> &input)
{
    
}
