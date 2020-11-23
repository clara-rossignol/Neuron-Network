#ifndef NEURONNETWORK_NETWORK_H
#define NEURONNETWORK_NETWORK_H


#include "Neuron.h"
#include "constants.h"

/*!
   This is a Network class which stores all the neurons
 */
class Network
{
public:

///@{
    /*!
        @param neurons all neurons that will form the whole network
     */
   Network(const std::vector<Neuron>& neurons);

   Network(size_t s, double pE);
   Network() = default;

///@}

///@{
    /*!
     * *setConnections* makes the entering connections for all neurons in the network.
     @param meanIntensity the mean intensity of a connection
     @param meanConnectivity the mean number of entering connections in one neuron
     */
    void setConnections(double meanIntensity, double meanConnectivity);

    void setNeuronConnections(double meanIntensity, double meanConnectivity, Neuron& neuron);

    /*!
     * *update* sets all neurons behavior during the simulation
     */
    void update();
    
     
    void print_params(std::ostream *_outstr);
    /*void print_sample(std::ostream *_outstr);*/
    void print_spikes(std::ostream *_outstr);

    const std::vector<Neuron> &getNeurons() const;
///@}

protected:
    std::vector<Neuron> neurons;
};

#endif //NEURONNETWORK_NETWORK_H
