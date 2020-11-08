#ifndef NEURONNETWORK_NETWORK_H
#define NEURONNETWORK_NETWORK_H

#include <vector>
#include "Neuron.h"

/*!
   This is a Network class which stores all the neurons
 */
class Network
{
public :

///@{
    /*!
        @param neurons all neurons that will form the whole network
     */
   Network(const std::vector<Neuron>& neurons ) : neurons(neurons){};
///@}

///@{
    /*!
     * *setConnections* makes the entering connections for all neurons in the network.
     @param meanIntensity the mean intensity of a connection
     @param meanConnectivity the mean number of entering connections in one neuron
     */
    void setConnections(double meanIntensity, double meanConnectivity);

    /*!
     * *update* sets all neurons behavior during the simulation
     */
    void update();
///@}

private :
    std::vector<Neuron> neurons;
};

#endif //NEURONNETWORK_NETWORK_H