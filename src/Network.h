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
/*! \name Constructors
 */
///@{
	/*!
   \param neurons: all neurons that will form the network
   */
   Network(const std::vector<Neuron>& neurons);

   /*! The network will be completed with
   \param s (size_t): the size of the network
   \param prop (TypesProportions) 
   */
   Network(size_t s, const TypesProportions& prop);
   /*!
   Defaulted default constructor: the compiler will define the implicit default constructor even if other constructors are present.
   */
   Network() = default;
///@}

	/*!
     * *setConnections* makes the entering connections for all neurons in the network.
     \param meanIntensity the mean intensity of a connection (double)
     \param meanConnectivity the mean number of entering connections in one neuron (double)
     */
    virtual void setConnections(double meanIntensity, double meanConnectivity);

    virtual void setNeuronConnections(double meanIntensity, double meanConnectivity, Neuron& neuron);

    /*!
     Sets all neurons behavior during the simulation
     */
    void update();
    
    /*! \name Output
     * These methods will print the different output files.
    * \param *_outstr: an ostream
    */
    ///@{
    /*! Prints the different parameters \p a, \p b, \p c, \p d, if the neuron is \p inhibitory or not, the \p degree (number of connections towards the neuron) and the \p valence (sum of all connections' intensities).
     */
    void print_params(std::ostream *_outstr);
    /*! Prints the \ref membrane_potential, \ref recovery_variable and \ref current from 1 neuron of each type present in the Network.
     */
    void print_sample(std::ostream *_outstr);
    /*! Prints a matrix with N columns (N = number of neurons in the Network) and T lines (T = number of steps in the simulation) with the value 1 if a neuron is firing and 0 otherwise.
     */
    void print_spikes(std::ostream *_outstr);
    ///@}
    
    /*!
     It returns the neurons.
     * \return neurons (vector<Neuron>)
     */
    const std::vector<Neuron> &getNeurons() const;

/*! \name Destructor
 */
///@{
    virtual ~Network() = default;
///@}

protected:
 /*!
     A set of neurons
     */
    std::vector<Neuron> neurons;
    std::vector<int> indexes;
};

#endif //NEURONNETWORK_NETWORK_H
