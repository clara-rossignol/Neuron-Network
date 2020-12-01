#ifndef NEURONNETWORK_DISPNETWORK_H
#define NEURONNETWORK_DISPNETWORK_H

#include "Network.h"
/*!
 * \class DispNetwork
   \brief This is another type of \ref Network.
   
   This is an extension, representing an overdispersed network:
   for each neuron the connection will be set to an exponential(1/connectivity), where exponential is a method of \ref Random.
 */
class DispNetwork : public Network
{
public:
    DispNetwork(size_t s, TypesProportions prop);
    DispNetwork(const std::vector<Neuron> &neurons);
    void setConnections(double meanIntensity, double meanConnectivity) override;
};


#endif //NEURONNETWORK_DISPNETWORK_H
