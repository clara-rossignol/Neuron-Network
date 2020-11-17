#ifndef NEURONNETWORK_DISPNETWORK_H
#define NEURONNETWORK_DISPNETWORK_H

#include "Network.h"

class DispNetwork : public Network
{
public:
    DispNetwork(const std::vector<Neuron> &neurons);
    void setConnections(double meanIntensity, double meanConnectivity);
};


#endif //NEURONNETWORK_DISPNETWORK_H
