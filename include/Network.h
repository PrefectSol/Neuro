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
    Network(const std::vector<int> &networkStruct, Vector &networkOffset, int learningRate);
    
    ~Network();

    uint32_t runTrainNetwork(const std::vector<std::pair<double, double>> &inputData, const std::vector<double> &outputData);

protected:

private:
    const int learningRate;

    typedef struct networkModel 
    {
        Vector **neuronLayers;
        int neuronLayersCount;

        Matrix **weightsLayers;
        int weightsLayersCount;

        Vector *offsetLayers;
    } networkModel;

    networkModel network;

    uint32_t propagateForward(const std::pair<double, double> &input);
};

#endif // !NETWORK_H