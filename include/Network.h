#ifndef NETWORK_H
#define NETWORK_H

#define VIEW_ERROR_FALSE

#include <iostream>
#include <vector>

#include "AuditLog.h"
#include "Algorithm.h"
#include "Math.h"

class Network 
{
public:    
    // Feed Forward Model
    Network(const std::vector<int> &networkStruct, const Functions &func, double bias, double learningRate);
    
    ~Network();

    uint32_t runTrainNetwork(const std::vector<std::pair<double, double>> &inputData, const std::vector<double> &outputData);

    uint32_t calculate(const std::pair<double, double> &input, double *output);

protected:

private:
    const double learningRate;
    const double bias;

    double (*activationFunc)(double x);
    double (*derivativeFunc)(double x);

    double error;

    typedef struct networkModel 
    {
        Vector **neuronLayers;
        int neuronLayersCount;

        Vector **neuronErrors;
        int neuronErrorsCount;

        Matrix **weightsLayers;
        int weightsLayersCount;
    } networkModel;

    networkModel network;

    uint32_t propagateForward(const std::pair<double, double> &input);

    uint32_t propagateBackward(double correctOutput);

    double getOutput();

    uint32_t calculateError(double correctOutput);

    uint32_t updateWeights();

    void printModel();

    void printOutput();
};

#endif // !NETWORK_H