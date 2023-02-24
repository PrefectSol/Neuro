#ifndef NETWORK_H
#define NETWORK_H

#define VIEW_ERROR

#include <iostream>
#include <array>
#include <vector>

#include "AuditLog.h"
#include "Algorithm.h"

#include "Math/BasicOperations.hpp"
#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"

class Network 
{
public:
    // Feed Forward Model
    Network(const std::vector<int> &networkStruct, const Functions &func, double bias, double learningRate,
            double epochs, bool isAdaptive = false, double decayRate = 0.5f, double targetAccuracy = -1.f);
    
    ~Network();

    // Feed Forward Model
    template<typename T1, typename T2, size_t size1, size_t size2>
    uint32_t runTrainNetwork(const std::vector<std::array<T1, size1>> &inputData, const std::vector<std::array<T2, size2>> &outputData);

protected:

private:
    const bool isAdaptive;
    const double decayRate;
    const double epochs;
    const double targetAccuracy;

    double learningRate;
    double bias;

    double (*activationFunc)(double x);
    double (*derivativeFunc)(double x);

    double mse;

    typedef struct networkModel 
    {
        Vector<double> **neuronLayers;
        size_t neuronLayersCount;

        Vector<double> **neuronErrors;
        size_t neuronErrorsCount;

        Matrix<double> **weightsLayers;
        size_t weightsLayersCount;
    } networkModel;

    networkModel network;

    template<typename T, size_t size>
    uint32_t propagateForward(const std::array<T, size> &input);

    template<typename T, size_t size>
    uint32_t propagateBackward(const std::array<T, size> &correctOutput);

    template<typename T, size_t size>
    uint32_t calculateMse(const std::array<T, size> &correctOutput);

    uint32_t updateWeights();

    void updateBias();

    void updateLearningRate();
};

template<typename T1, typename T2, size_t size1, size_t size2>
uint32_t Network::runTrainNetwork(const std::vector<std::array<T1, size1>> &inputData, const std::vector<std::array<T2, size2>> &outputData)
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
        std::cout << mse << std::endl;
    #endif // DEBUG
    
        if (mse <= targetAccuracy)
        {
            return ErrorCode::success;
        }
    }

    return ErrorCode::failedToAchieveTargetAccuracy;
}

template<typename T, size_t size>
uint32_t Network::propagateForward(const std::array<T, size> &input)
{
    const T *inputLayer = input.data();

    T activatedLayer[size];
    for(int i = 0; i < size; i++)
    {
        activatedLayer[i] = activationFunc(inputLayer[i]);
    }

    uint32_t isSetInput = network.neuronLayers[0]->setSizedData(activatedLayer, size);
    if (isSetInput != ErrorCode::success)
    {
        return isSetInput;
    }

    for(int i = 1; i < network.neuronLayersCount; i++)
    {
        const size_t layerSize = network.neuronLayers[i]->getSize();

        Vector<double> biasLayer(bias, layerSize);
        Vector<double> newNeuronValues(layerSize);
        
        try
        {
            Vector<double> result1 = *network.weightsLayers[i - 1] * *network.neuronLayers[i - 1];
            Vector<double> result2 = result1 + biasLayer;

            uint32_t isActivateCode = activateNeuronLayer(activationFunc, result2, network.neuronLayers[i]);
            if (isActivateCode != ErrorCode::success)
            {
                return isActivateCode;
            }
        }
        catch(...)
        {
            return ErrorCode::operationsFailed;
        }
    }
    
    return ErrorCode::success;
}

template<typename T, size_t size>
uint32_t Network::propagateBackward(const std::array<T, size> &correctOutput)
{
    uint32_t isCalculateErrorCode = calculateMse(correctOutput);
    if (isCalculateErrorCode != ErrorCode::success)
    {
        return isCalculateErrorCode;
    }

    uint32_t isUpdateWeightsCode = updateWeights();
    if (isUpdateWeightsCode != ErrorCode::success)
    {
        return isUpdateWeightsCode;
    }

    updateBias();

    if (isAdaptive)
    {
        updateLearningRate();
    }

    return ErrorCode::success;
}

template<typename T, size_t size>
uint32_t Network::calculateMse(const std::array<T, size> &correctOutput)
{
    T *nums = network.neuronLayers[network.neuronLayersCount - 1]->vector;

    for (size_t i = 0; i < size; i++) 
    {
        mse += std::pow(nums[i] - correctOutput[i], 2);
    }
    mse /= (size == 1) ? 2 : size;

    Vector<double> mseVector(mse, size);
    network.neuronErrors[network.neuronErrorsCount - 1]->setSizedData(mseVector.vector, size);

    for(int i = network.neuronErrorsCount - 2; i >= 0; i--)
    {
        const int layerSize = network.neuronErrors[i]->getSize();

        Vector<double> newErrorLayer(layerSize);
        Matrix<double> transposeWeight(network.weightsLayers[i + 1]->getCols(), network.weightsLayers[i + 1]->getRows());
        
        uint32_t isTransposeCode = transposeMatrix(*network.weightsLayers[i + 1], &transposeWeight);
        if (isTransposeCode != ErrorCode::success)
        {
            return isTransposeCode;
        }

        try
        {
            Vector<double> newErrorLayer = transposeWeight * *network.neuronErrors[i + 1];
            uint32_t isSetDataCode = network.neuronErrors[i]->setSizedData(newErrorLayer.vector, layerSize);
            if (isSetDataCode != ErrorCode::success)
            {
                return isSetDataCode;
            }
        }
        catch(...)
        {
            return ErrorCode::cannotTransposeMatrix;
        }
    }

    return ErrorCode::success;
}

#endif // !NETWORK_H