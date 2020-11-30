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
  /** Initialises the network with neurons
   @param neurons: a set of neurons 
   */
    ConstNetwork(const std::vector<Neuron> &neurons);
    /*!
     Sets the connections.
     @param meanIntensity the mean intensity of a connection
     @param meanConnectivity the mean number of entering connections in one neuron
     */
    void setConnections(double meanIntensity, double meanConnectivity);
    /*!
     Sets 
     @param meanIntensity the mean intensity of a connection
     @param meanConnectivity the mean number of entering connections in one neuron
     @param neuron
     */
    void setNeuronConnections(double meanIntensity, double meanConnectivity, Neuron& neuron);
};


#endif //NEURONNETWORK_CONSTNETWORK_H
