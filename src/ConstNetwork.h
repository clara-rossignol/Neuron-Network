#ifndef CONSTNETWORK_H
#define CONSTNETWORK_H

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
/*! \name Initialization
 */
///@{
  /** Initialises the network as explained in the description of the class
   @param s: size of the network, number of neurons
   @param prop : the proportions of each type of neurons
   */
	ConstNetwork(size_t s, TypesProportions prop);

///@}

    /*!
    Sets the connections.
    @param meanIntensity: the mean intensity of a connection
    @param meanConnectivity: the mean number of entering connections 
    in one neuron
    */
    void setConnections(double meanIntensity, double meanConnectivity) override;
    /*!
     Sets
     @param meanIntensity: the mean intensity of a connection
     @param meanConnectivity: the mean number of entering connections 
     in one neuron
     @param neuron
     */
    void setNeuronConnections(double meanIntensity, double meanConnectivity,
                              Neuron& neuron) override;
};


#endif //CONSTNETWORK_H
