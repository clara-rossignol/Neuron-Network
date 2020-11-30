#ifndef NEURONNETWORK_DISPNETWORK_H
#define NEURONNETWORK_DISPNETWORK_H

#include "Network.h"
/*!
 * \class DispNetwork
   \brief This is another type of \ref Network.
   
   This is an extension, representing an overdispersed network:
   for each neuron the connection will be set to an exponential(1/connectivity), where exponential is a method of \ref RandomNumbers
 */
class DispNetwork : public Network
{
public:
/** Initialises the network with neurons
   @param neurons: a set of neurons 
   */
    DispNetwork(const std::vector<Neuron> &neurons);
    /*!
     Sets the connections, as explained in the description of the class.
     @param meanIntensity the mean intensity of a connection
     @param meanConnectivity the mean number of entering connections in one neuron
     */
    void setConnections(double meanIntensity, double meanConnectivity);
};


#endif //NEURONNETWORK_DISPNETWORK_H
