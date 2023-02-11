#include "Network.h"

Network::Network(const std::vector<int> &networkStruct, double bios, double learningRate)
    : learningRate(learningRate), bios(bios)
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

    network.weightsErrorsCount = networkStruct.size() - 1;
    network.weightsErrors = new Matrix*[network.weightsErrorsCount];
    for(int i = 0; i < network.weightsErrorsCount; i++)
    {
        network.weightsErrors[i] = new Matrix(networkStruct[i + 1], networkStruct[i], false);
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

    for(int i = 0; i < network.weightsErrorsCount; i++)
    {
        delete network.weightsErrors[i];
    }
    delete[] network.weightsErrors;
}

uint32_t Network::runTrainNetwork(const std::vector<std::pair<double, double>> &inputData, const std::vector<double> &outputData)
{
    for(int i = 0; i < inputData.size(); i++)
    {
        uint32_t propagateForwardCode = propagateForward(inputData[i]);
        if (propagateForwardCode != ErrorCode::success)
        {
            return propagateForwardCode;
        }

        calculateError(outputData[i]);
        updateWeights();
    }

    return ErrorCode::success;
}

uint32_t Network::propagateForward(const std::pair<double, double> &input)
{
    double (*activationFunc)(double x) = ActivationFunctions::sigmoid;

    double inputLayer[2] = { activationFunc(input.first), activationFunc(input.second) };
    uint32_t isSetInput = network.neuronLayers[0]->setSizedData(inputLayer, 2);
    if (isSetInput != ErrorCode::success)
    {
        return isSetInput;
    }

    for(int i = 1; i < network.neuronLayersCount; i++)
    {
        const int layerSize = network.neuronLayers[i]->getSize();

        Vector biosLayer(bios, layerSize);
        Vector matrix2vectorResult(layerSize);
        Vector vector2vectorResult(layerSize);
        Vector newNeuronLayer(layerSize);
        
        BasicOperations::multiplyMatrix2Vector(*network.weightsLayers[i - 1], *network.neuronLayers[i - 1], &matrix2vectorResult);
        BasicOperations::sumVector2Vector(matrix2vectorResult, biosLayer, &vector2vectorResult);
        BasicOperations::activateNeuronLayer(activationFunc, vector2vectorResult, &newNeuronLayer);
        
        network.neuronLayers[i]->setSizedData(newNeuronLayer.getAllElements(), newNeuronLayer.getSize());
    }
    
    printOutput();

    return ErrorCode::success;
}

void Network::calculateError(double outputData)
{
    double *nums = network.neuronLayers[network.neuronLayersCount - 1]->getAllElements();
    const double outputValue = nums[0];

    const double error = abs(outputData - outputValue);
}

void Network::updateWeights()
{
    // ...
}

void Network::printModel()
{
    std::cout << "--------------------------------" << std::endl;
    std::cout << "\t\tSTART VIEW" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    std::cout << "Layers:" << std::endl;
    for(int k = 0; k < network.neuronLayersCount; k++)
    {
        std::cout << "\tLayer " << k << std::endl;
        double *layer = network.neuronLayers[k]->getAllElements();
        for(int j = 0; j < network.neuronLayers[k]->getSize(); j++)
        {
            std::cout << "\t\t\t" << layer[j] << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;

    std::cout << "WEIGHTS:" << std::endl;
    for(int k = 0; k < network.weightsLayersCount; k++)
    {
        std::cout << "\tLayer: " << k << std::endl;
        Matrix *layer = network.weightsLayers[k];
        for(int j = 0; j < layer->getRows(); j++)
        {
            for(int c = 0; c < layer->getCols(); c++)
            {
                double element;
                layer->getElement(j, c, &element);
                std::cout << element << "\t";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "--------------------------------" << std::endl;
}

void Network::printOutput()
{
    double *nums = network.neuronLayers[network.neuronLayersCount - 1]->getAllElements();
    for(int i = 0; i < network.neuronLayers[network.neuronLayersCount - 1]->getSize(); i++)
    {
        std::cout << nums[i] << std::endl;
    } 
}