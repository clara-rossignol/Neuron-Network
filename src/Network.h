#ifndef NEURONNETWORK_NETWORK_H
#define NEURONNETWORK_NETWORK_H


#include "Neuron.h"
#include "constants.h"

/*!
 * \class Network
   \brief This is a Network class which stores all the neurons.
   
   A Network represents a set of neurons and their connections.
 */
class Network
{
public:

///@{
  /*! Constructors:
   @param neurons: all neurons that will form the whole network
   */
   Network(const std::vector<Neuron>& neurons);

   /** The network will be completed with
   @param s (size_t), the size of the network
   @param prop (TypesProportions): 
   */
   Network(size_t s, TypesProportions prop);
   /**  
   Defaulted default constructor: the compiler will define the implicit default constructor even if other constructors are present.
   */
   Network() = default;

///@}

///@{
    /*!
     * *setConnections* makes the entering connections for all neurons in the network.
     @param meanIntensity the mean intensity of a connection
     @param meanConnectivity the mean number of entering connections in one neuron
     */
    virtual void setConnections(double meanIntensity, double meanConnectivity);

    virtual void setNeuronConnections(double meanIntensity, double meanConnectivity, Neuron& neuron);

    /*!
     *Sets all neurons behavior during the simulation
     */
    void update();
    /*! These methods will print the different output files.
    * @param *_outstr: an ostream
    */
    ///@{
    void print_params(std::ostream *_outstr);
    void print_sample(std::ostream *_outstr, size_t n);
    void print_spikes(std::ostream *_outstr);
    ///@}
    const std::vector<Neuron> &getNeurons() const;
///@}

    virtual ~Network() = default;

protected:
    std::vector<Neuron> neurons;
};

#endif //NEURONNETWORK_NETWORK_H
