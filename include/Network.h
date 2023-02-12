#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <vector>

#include "AuditLog.h"
#include "Algorithm.h"
#include "Math.h"

class Network 
{
public:    
    // Feed Forward Model
    Network(const std::vector<int> &networkStruct, double bias, double learningRate);
    
    ~Network();

    uint32_t runTrainNetwork(const std::vector<std::pair<double, double>> &inputData, const std::vector<double> &outputData);

protected:

private:
    const double learningRate;
    const double bias;

    typedef struct networkModel 
    {
        Vector **neuronLayers;
        int neuronLayersCount;

        Matrix **weightsLayers;
        int weightsLayersCount;

        Matrix **weightsErrors;
        int weightsErrorsCount;
    } networkModel;

    networkModel network;

    uint32_t propagateForward(const std::pair<double, double> &input);

    void calculateError(double outputData);

    void updateWeights();

    void printModel();

    void printOutput();
};

#endif // !NETWORK_H