#ifndef NETWORK_H
#define NETWORK_H

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
/*! \name Initialization
 */
///@{
  /*! A set of neurons of size *size* is created according 
   * to proportions given in *prop*. 
   * The last position in the network of each type of neurons is
   * recorded in \ref indexes in order to print neuron type 
   * specific values in output files.
   * \param size: the size of the network
   * \param prop: all proportions corresponding to each type of neurons
   */
   Network(size_t size, const TypesProportions& prop);
   
  /*! \name Destructor
   */
    virtual ~Network() = default;
///@}

	/*!
   * *setConnections* makes the entering connections 
   * for all neurons in the network.
   * \param meanIntensity: the mean intensity of a connection 
   * \param meanConnectivity: the mean number of entering connections 
   * in one neuron 
   */
    virtual void setConnections(double meanIntensity, double meanConnectivity);
    
  /*!
   * *setNeuronConnections* makes the entering connections for one neuron
   * Creates a set of inhibitory senders and a set of excitatory senders 
   * that will be assembled in neuron \ref setConnections. 
   * Those two ensembles have been created in order to facilitate
   * \ref Neuron::currentCalculation in Neuron and \ref printSamples
   * \param meanIntensity: the mean intensity of a connection 
   * \param meanConnectivity: the mean number of entering connections
   *  in one neuron 
   * \param neuron: the neuron for which connections are set
   */
    virtual void setNeuronConnections(double meanIntensity, double meanConnectivity, Neuron& neuron);

  /*!
   * Sets all neurons behavior during the simulation in order to have 
   * all firing neurons influencing the current at the same time,
   * the \ref firing of all neurons is updated separately
   */
    void update(double thal);
    
  /*! \name Output
   * These methods will print the different output files.
   * \param *_outstr: an ostream
   */
    ///@{
  /*! 
   * Prints the different parameters \p a, \p b, \p c, \p d, 
   * if the neuron is \p inhibitory or not, the \p degree (number of 
   * connections towards the neuron) and the \p valence (sum of all 
   * connections' intensities).
   */
  void printParams(std::ostream *_outstr);
  /*! 
   * Prints the \ref membranePotential, \ref recoveryVariable and 
   \ref current from 1 neuron of each type present in the Network.
   */
  void printSample(std::ostream *_outstr);
  /*! 
   * Prints a matrix with N columns (N = number of neurons in the Network) 
   * and T lines (T = number of steps in the simulation) with the value
   * 1 if a neuron is firing and 0 otherwise.
   */
  void printSpikes(std::ostream *_outstr);
    ///@}
    
  /*!
  It returns the neurons.
  * \return neurons (vector<Neuron>)
     */
    const std::vector<Neuron> &getNeurons() const;
    /*!
     * It returns the indexes.
     * \return indexes (vector<int>)
     */
    const std::vector<int> &getIndexes() const;


protected:
 /*!
  * A set of neurons
  */
    std::vector<Neuron> neurons;
    std::vector<int> indexes;
};

#endif //NETWORK_H
