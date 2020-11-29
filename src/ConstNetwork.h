#ifndef NEURONNETWORK_CONSTNETWORK_H
#define NEURONNETWORK_CONSTNETWORK_H

#include "Network.h"
/*!
 * \class ConstNetwork
   \brief This is another type of \ref Network. 
   
   This is an extension, representing a constant network.
   Here each neuron has exactly c connections.
 */
class ConstNetwork : public Network
{
public:
    ConstNetwork(const std::vector<Neuron> &neurons);
    void setConnections(double meanIntensity, double meanConnectivity);
    void setNeuronConnections(double meanIntensity, double meanConnectivity, Neuron& neuron);
};


#endif //NEURONNETWORK_CONSTNETWORK_H
