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

    void runTrainNetwork(std::vector<std::pair<int, int>> &inputData, std::vector<int> &outputData);

    void propagateForward(const std::pair<int, int> &input);

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
};

#endif // !NETWORK_H