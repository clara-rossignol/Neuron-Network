#ifndef NEURONNETWORK_CONSTNETWORK_H
#define NEURONNETWORK_CONSTNETWORK_H

#include "Network.h"

class ConstNetwork : public Network
{
public:
    ConstNetwork(const std::vector<Neuron> &neurons);
    void setConnections(double meanIntensity, double meanConnectivity);
    void setNeuronConnections(double meanIntensity, double meanConnectivity, Neuron& neuron);
};


#endif //NEURONNETWORK_CONSTNETWORK_H
