#ifndef NEURON_H
#define NEURON_H

#include "constants.h"

/*!
 * \class Neuron
   \brief This is a Neuron class which generates neurons.
  
    A neuron's cellular properties are defined by 4 parameters 
    \p a, \p b, \p c, \p d and its inhibitory or excitatory quality.
    The Neuron types are provided in \ref constants.h as a map 
    NeuronTypes and identified by a 2 or 3-letter string.
*/

class Neuron
{

public:
    /*! \name Initializing
    */
///@{
   /*! The constructor initializes the neuron. 
    * By default the neuron is not in a firing state.
    * To achieve heterogeneity in our model, if the neuron is either 
    * a *regular spiking* (RS) or a *fast spiking* (FS) neuron i
    * ts 4 parameters \p a, \p b, \p c and \p d are recalculated 
    * with the help of a random variable. 
    * \param type: the type of the neuron
    * \param isFiring: the firing state of the neuron
    */
    Neuron(const std::string& type, bool isFiring = false);
    
     /*! \name Destructor
     */
    ~Neuron();
///@}

    /*!
    The _current is calculated for the neuron. 
    * Only firing senders influence the calculation.
    * \return current (double)
    */
    void currentCalculation(double thal);
    /*!
    A neuron is updated : its \ref membranePotential and 
    * its \ref recoveryVariable are updated according to the neuron's
    * firing state i.e. \ref willFire and \ref firing.
    */
    void update(double thal);
    /*!
    After firing, the neuron is reset: \ref membranePotential is set to
    \p c, \ref recoveryVariable is increased by \p d.
    */
    void reset();
	/*! \return membranePotential (double)
	*/
	double getMembranePotential() const;
	/*!  \return recoveryVariable (double)
	*/
	double getRecoveryVariable() const;
    /*!
    The \ref membranePotential is updated according 
    * to the Izhikevich equations.
    */
    void setMembranePotential();
    /*!
    The \ref recoveryVariable is updated according 
    * to the Izhikevich equations.
    * \param potential (double)
    */
    void setRecoveryVariable(double potential);
    /*!
    A neuron is firing if its membranePotential exceeds the 
    * firing treshold, 30 mV.
    * \return true if the neuron is in a firing state, false otherwise
    */
    bool isFiring() const;
    /*!
     * \return true if a neuron is inhibitory, false otherwise
    */
    bool isInhibitor() const;
	/*!
	 * \return the \ref nParams parameters of the neuron (NParams)
	*/
	NParams getParameters() const;
	/*!
	 * \return the type of the neuron
	 */
	std::string getType() const; 
    /*!
     * \return the connections: the neurons connected with the neuron
    */
    std::vector<Connection> getConnections() const;
    /*!
     * Creates all connections: connections are first made of inhibitory 
     * senders, following by excitatory senders.
     * The exact position of the last inhibitory neuron is 
     * recorded in \ref _nInhibitory.
     * Connections are created in this way to 
     * facilitate \ref currentCalculation() and
     * \ref Network::print_params() in Network
     * \param inhib (vector<Connection>) all inhibitory senders
     * \param excit (vector<Connection>) all excitatory senders
    */
    void setConnections(const std::vector<Connection> &inhib, 
    const std::vector<Connection> &excit);


    bool isGoingToFire() const;
    /*!
     * Sets the \ref firing.
     \param fire (bool)
    */
    void setFiring(bool fire);
     /*!
     *Gets the number of inhibitory neurons
    */
    size_t getNInhibitory() const;
    /*!
     * Gets the current value
    */
    double getCurrent() const;

    
private:
	/*! \name Firing state of the neuron
	 */
	///@{
    bool willFire;
    bool firing;
    ///@}

    /*! \name Dynamic variables
    */
    ///@{
    double membranePotential;
    double recoveryVariable;
    double current;
    ///@}
    
    /*! \name Neuron parameters 
    \p a, \p b, \p c, \p d, and the boolean \p inhib
    */
    NParams nParams;
    
    /*! \name Type
     */
    ///@{
    std::string type;
    ///@}
    
    /*! \name Connections
      * A vector of connections : \p sender, a pointer to a neuron
      * and the \p intensity of the connection
    */
    std::vector<Connection> connections;

    size_t nInhibitory;
};

#endif //NEURON_H
