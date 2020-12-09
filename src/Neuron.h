#ifndef NEURON_H
#define NEURON_H

#include "constants.h"

/*!
 * \class Neuron
   \brief This is a Neuron class  which generates neurons.
  
    A neuron's cellular properties are defined by 4 parameters \p a, \p b, \p c, \p d and its inhibitory or excitatory quality.
    The Neuron types are provided in \ref constants.h as a map NeuronTypes and identified by a 2 or 3-letter string.
*/

class Neuron
{

public:
    /*! \name Initializing
    The constructor initializes the neuron. By default the neuron is not in a firing state.
    * To achieve heterogeneity in our model, if the neuron is either a *regular spiking* (RS) or a *fast spiking* (FS) neuron its 4 parameters \p a, \p b, \p c and \p d are recalculated with the help of a random variable. 
    * \param type (string): the type of the neuron
    * \param isfiring(bool): the firing state of the neuron
    */
///@{
    Neuron(const std::string& type, bool isfiring = false);
///@}

    /*!
    The current is calculated for each neuron.
    * \return current (double)
    */
    void currentCalculation();
    /*!
    A neuron is updated : its \ref membrane_potential and its \ref recovery_variable are updated according to the neuron's firing state i.e. \ref willFire and \ref firing.
    */
    void update();
    /*!
    After firing, the neuron is reset: \ref membrane_potential is set to \p c, \ref recovery_variable is increased by \p d.
    */
    void reset();
	/*! \return membrane_potential (double)
	*/
	double getMembranePotential() const;
	/*!  \return recovery_variable (double)
	*/
	double getRecoveryVariable() const;
    /*!
    The \ref membrane_potential is updated according to the Izhikevich equations.
    */
    void setMembranePotential();
    /*!
    The \ref recovery_variable is updated according to the Izhikevich equations.
    * \param potential (double)
    */
    void setRecoveryVariable(double potential);
    /*!
    A neuron is firing if its membrane potential exceeds the firing treshold, 30 mV.
    * \return true if the neuron is in a firing state, false otherwise (bool)
    */
    bool isFiring() const;
    /*!
     * \return true if a neuron is inhibitory, false otherwise (bool)
    */
    bool isInhibitor() const;
	/*!
	 * \return the parameters of the neuron (NParams)
	*/
	NParams getParameters() const;
	/*!
	 * \return the type of the neuron (string)
	 */
	std::string getType() const; 
    /*!
     * \return the connections : the neurons connected with the neuron (vector<Connection>)
    */
    std::vector<Connection> getConnections() const;
    /*!
     * ??????
    */
    void setConnections(const std::vector<Connection> &inhib, const std::vector<Connection> &excit);
    /*!
     * ??????
     * \param inhib (vector<Connection>)
     * \param excit (vector<Connection>)
    */
    bool isGoingToFire() const;
    /*!
     * Sets the \ref firing.
     \param fire (bool)
    */
    void setFiring(bool fire);

    size_t getNInhibitory() const;
    double getCurrent() const;


    /*! \name Destructor
     */
    ///@{
    ~Neuron();
    ///@} 
    
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
    double membrane_potential;
    double recovery_variable;
    double current;

private:
    ///@}
    
    /*! \name Neuron parameters 
    \p a, \p b, \p c, \p d, and the boolean \p inhib
    */
    NParams nparams;
    
    /*! \name Type
     */
    ///@{
    std::string type;
    ///@}
    
    /*! \name Connections
      * A vector of connections : \p sender, a pointer to a neuron and the \p intensity of the connection
    */
    std::vector<Connection> connections;

    size_t n_inhibitory;

};

#endif //NEURON_H
