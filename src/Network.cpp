#include "Network.h"

Network::Network(const std::vector<int> &networkStruct, const Functions &func, double bias, double learningRate)
    : learningRate(learningRate), bias(bias)
{
    network.neuronLayersCount = networkStruct.size();
    network.neuronLayers = new Vector*[network.neuronLayersCount];
    for(int i = 0; i < network.neuronLayersCount; i++)
    {
        network.neuronLayers[i] = new Vector(networkStruct[i]);
    }

    network.neuronErrorsCount = networkStruct.size() - 1;
    network.neuronErrors = new Vector*[network.neuronErrorsCount];
    for(int i = 0; i < network.neuronErrorsCount; i++)
    {
        network.neuronErrors[i] = new Vector(networkStruct[i + 1]);
    }

    network.weightsLayersCount = networkStruct.size() - 1;
    network.weightsLayers = new Matrix*[network.weightsLayersCount];
    for(int i = 0; i < network.weightsLayersCount; i++)
    {
        network.weightsLayers[i] = new Matrix(networkStruct[i + 1], networkStruct[i]);
    }

    switch (func)
    {
    case 0:
        activationFunc = ActivationFunctions::linear;
        derivativeFunc = DerivativeFunctions::linear;
        break;

    case 1:
        activationFunc = ActivationFunctions::semiLinear;
        derivativeFunc = DerivativeFunctions::semiLinear;
        break;

    case 2:
        activationFunc = ActivationFunctions::sigmoid;
        derivativeFunc = DerivativeFunctions::sigmoid;
        break;

    case 3:
        activationFunc = ActivationFunctions::hyperbolicTangent;
        derivativeFunc = DerivativeFunctions::hyperbolicTangent;
        break;

    case 4:
        activationFunc = ActivationFunctions::hyperbolic;
        derivativeFunc = DerivativeFunctions::hyperbolic;
        break;

    case 5:
        activationFunc = ActivationFunctions::exponential;
        derivativeFunc = DerivativeFunctions::exponential;
        break;

    case 6:
        activationFunc = ActivationFunctions::quadratic;
        derivativeFunc = DerivativeFunctions::quadratic;
        break;

    case 7:
        activationFunc = ActivationFunctions::sign;
        derivativeFunc = DerivativeFunctions::sign;
        break;

    case 8:
        activationFunc = ActivationFunctions::single;
        derivativeFunc = DerivativeFunctions::single;
        break;

    default:
        throw std::runtime_error("Cannot find function.");
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

    for(int i = 0; i < network.neuronErrorsCount; i++)
    {
        delete network.neuronErrors[i];
    }
    delete[] network.neuronErrors;
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

        uint32_t propagateBackwardCode = propagateBackward(outputData[i]);
        if (propagateBackwardCode != ErrorCode::success)
        {
            return propagateBackwardCode;
        }

    #ifdef VIEW_ERROR
        std::cout << "MSE: " << error << std::endl;
    #endif // !VIEW_ERROR
    }

    return ErrorCode::success;
}

uint32_t Network::propagateForward(const std::pair<double, double> &input)
{
    double inputLayer[2] = { activationFunc(input.first), activationFunc(input.second) };
    uint32_t isSetInput = network.neuronLayers[0]->setSizedData(inputLayer, 2);
    if (isSetInput != ErrorCode::success)
    {
        return isSetInput;
    }

    for(int i = 1; i < network.neuronLayersCount; i++)
    {
        const int layerSize = network.neuronLayers[i]->getSize();

        Vector biasLayer(bias, layerSize);
        Vector matrix2vectorResult(layerSize);
        Vector vector2vectorResult(layerSize);
        Vector newNeuronLayer(layerSize);
        
        BasicOperations::multiplyMatrix2Vector(*network.weightsLayers[i - 1], *network.neuronLayers[i - 1], &matrix2vectorResult);
        BasicOperations::sumVector2Vector(matrix2vectorResult, biasLayer, &vector2vectorResult);
        BasicOperations::activateNeuronLayer(activationFunc, vector2vectorResult, &newNeuronLayer);
        
        network.neuronLayers[i]->setSizedData(newNeuronLayer.getAllElements(), newNeuronLayer.getSize());
    }
    
    return ErrorCode::success;
}

uint32_t Network::propagateBackward(double correctOutput)
{
    calculateError(correctOutput);
    updateWeights();

    return ErrorCode::success;
}

uint32_t Network::calculateError(double correctOutput)
{
    double *nums = network.neuronLayers[network.neuronLayersCount - 1]->getAllElements();
    const double outputValue = nums[0];

    error = pow(correctOutput - outputValue, 2) / 2.0;
    network.neuronErrors[3]->setSizedData(&error, 1);

    for(int i = network.neuronErrorsCount - 2; i >= 0; i--)
    {
        const int layerSize = network.neuronErrors[i]->getSize();

        Vector newErrorLayer(layerSize);
        Matrix transposeWeight(network.weightsLayers[i + 1]->getCols(), network.weightsLayers[i + 1]->getRows());
        
        BasicOperations::transposeMatrix(*network.weightsLayers[i + 1], &transposeWeight);
        BasicOperations::multiplyMatrix2Vector(transposeWeight, *network.neuronErrors[i + 1], &newErrorLayer);

        network.neuronErrors[i]->setSizedData(newErrorLayer.getAllElements(), newErrorLayer.getSize());
    }

    return ErrorCode::success;
}

uint32_t Network::updateWeights()
{
    for(int i = 0; i < network.weightsLayersCount; i++)
    {
        const int layerRows = network.weightsLayers[i]->getRows();
        const int layerCols = network.weightsLayers[i]->getCols();

        double correctiveValues[layerRows][layerCols];
        for(int j = 0; j < layerRows; j++)
        {
            for(int k = 0; k < layerCols; k++)
            {
                correctiveValues[j][k] = network.weightsLayers[i]->matrix[j][k] + learningRate * network.neuronErrors[i]->vector[j] * derivativeFunc(network.neuronLayers[i]->vector[j]);
            }
        }

        Matrix corrective(layerRows, layerCols, correctiveValues);

        network.weightsLayers[i]->setData(corrective);
    }

    return ErrorCode::success;
}

double Network::getOutput()
{
    double *nums = network.neuronLayers[network.neuronLayersCount - 1]->getAllElements();
    return nums[0];
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

    std::cout << "Errors:" << std::endl;
    for(int k = 0; k < network.neuronErrorsCount; k++)
    {
        std::cout << "\tLayer " << k << std::endl;
        double *layer = network.neuronErrors[k]->getAllElements();
        for(int j = 0; j < network.neuronErrors[k]->getSize(); j++)
        {
            std::cout << "\t\t\t" << layer[j] << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;

}

void Network::printOutput()
{
    std::cout << getOutput() << std::endl;
}

uint32_t Network::calculate(const std::pair<double, double> &input, double *output)
{
    uint32_t propagateForwardCode = propagateForward(input);
    if (propagateForwardCode != ErrorCode::success)
    {
        return propagateForwardCode;
    }

    *output = getOutput();

    return ErrorCode::success;
}