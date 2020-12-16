#ifndef DISPNETWORK_H
#define DISPNETWORK_H

#include "Network.h"
/*!
 * \class DispNetwork
   \brief This is another type of \ref Network.
   
   This is an extension, representing an overdispersed network:
   for each neuron the connection will be set to an exponential(1/connectivity), 
   * where exponential is a method of \ref RandomNumbers.
 */
 
class DispNetwork : public Network
{
public:
	/*! \name Initialization
	 */
///@{
    /*! Initialize the networl as explained in the description of the class
   * \param size: the size of the network
   * \param prop: all proportions corresponding to each type of neurons
   */
    DispNetwork(size_t s, TypesProportions prop);
///@}

    /*!
    Sets the connections, as explained in the description of the class.
    @param meanIntensity: the mean intensity of a connection (double)
    @param meanConnectivity: the mean number of entering connections 
    in one neuron (double)
    */
    void setConnections(double meanIntensity, double meanConnectivity) override;
};


#endif //DISPNETWORK_H
