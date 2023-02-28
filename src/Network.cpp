#include "Network.h"

Network::Network(const std::vector<int> &networkStruct, const Functions &func, double bias, double learningRate,
                double epochs, bool isAdaptive, double decayRate, double targetAccuracy)
    : isAdaptive(isAdaptive), decayRate(decayRate), epochs(epochs), targetAccuracy(targetAccuracy)
{
    this->learningRate = learningRate;
    this->bias = bias;

    network.neuronLayersCount = networkStruct.size();
    network.neuronLayers = new Vector<double>*[network.neuronLayersCount];
    for(int i = 0; i < network.neuronLayersCount; i++)
    {
        network.neuronLayers[i] = new Vector<double>(networkStruct[i]);
    }

    network.neuronErrorsCount = networkStruct.size() - 1;
    network.neuronErrors = new Vector<double>*[network.neuronErrorsCount];
    for(int i = 0; i < network.neuronErrorsCount; i++)
    {
        network.neuronErrors[i] = new Vector<double>(networkStruct[i + 1]);
    }

    network.weightsLayersCount = networkStruct.size() - 1;
    network.weightsLayers = new Matrix<double>*[network.weightsLayersCount];
    for(int i = 0; i < network.weightsLayersCount; i++)
    {
        network.weightsLayers[i] = new Matrix<double>(networkStruct[i + 1], networkStruct[i]);
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

uint32_t Network::updateWeights()
{
    for(int i = 0; i < network.weightsLayersCount; i++)
    {
        const int layerRows = network.weightsLayers[i]->getRows();
        const int layerCols = network.weightsLayers[i]->getCols();

        Vector<double> derivativeLayer(network.neuronLayers[i]->getSize());
        uint32_t isDerivativeLayerCode = activateNeuronLayer(derivativeFunc, *network.neuronLayers[i], &derivativeLayer);
        if (isDerivativeLayerCode != ErrorCode::success)
        {
            return isDerivativeLayerCode;
        }
        
        Matrix<double> gradient = *network.neuronErrors[i] * derivativeLayer;
        Matrix<double> learningGradient = learningRate * gradient;

        Matrix<double> correctiveWeights = *network.weightsLayers[i] - learningGradient;

        // double correctiveValues[layerRows][layerCols];
        // for(int j = 0; j < layerRows; j++)
        // {
        //     for(int k = 0; k < layerCols; k++)
        //     {
        //         correctiveValues[j][k] = network.weightsLayers[i]->matrix[j][k] - learningRate * network.neuronErrors[i]->vector[j] * derivativeFunc(network.neuronLayers[i]->vector[j]);
        //     }
        // }

        // Matrix<double> corrective(layerRows, layerCols, correctiveValues);

        // std::cout << network.weightsLayers[i]->getCols() << "\t" << network.weightsLayers[i]->getRows() << std::endl;
        // std::cout << correctiveWeights.getCols() << "\t" << correctiveWeights.getRows() << std::endl;


        uint32_t isSetDataCode = network.weightsLayers[i]->setData(correctiveWeights);
        if (isSetDataCode != ErrorCode::success)
        {
            return isSetDataCode;
        }
    }

    return ErrorCode::success;
}

void Network::updateBias()
{
    bias += learningRate * mse;
}

void Network::updateLearningRate()
{
    learningRate *= pow(decayRate, epochs);
}