#ifndef NEURON_H
#define NEURON_H
#include "constants.h"


/*!
 * \class Neuron
   \brief This is a Neuron class in which we create neurons.
  
    A neuron is defined by 4 parameters \p a, \p b, \p c, \p d and its inhibitory or excitatory quality.
    The Neuron types are provided in \ref comstants.h as a map NeuronTypes and identified by a 2 or 3-letter string.
*/

class Neuron
{

public:
    /*!
    The constructor initializes the neuron
    */
    Neuron(std::string type, bool isfiring = false);

    /*!
    The current is calculated for each neuron
    */
    double currentCalculation();
    /*!
    A neuron is updated 
    */
    void update();
    /*!
    After firing, the neuron is reset: \ref membrane_potential is set to \p c, \ref recovery_variable is increased by \p d.
    */
    void reset();

	/**It will print the membrane potential, the recovery variable and the input of a sample neuron. */
	std::string print_sample();
    ///@}
	/*! membrane_potential getter
	*/
	double getMembranePotential() const;
	/*!  recovery_variable getter
	*/
	double getRecoveryVariable() const;
    /*!
    The \ref membrane_potential is updated according to the Izhikevich equations.
    */
    void setMembranePotential();
    /*!
    The \ref recovery_variable is updated according to the Izhikevich equations.
    */
    void setRecoveryVariable(double potential);
    /*!
    A neuron is firing if its membrane potential exceeds the T, the firing treshold, 30 mV
    */
    bool isFiring() const;
    /*!
    Check if a neuron is inhibitory or not
    */
    bool isInhibitor() const;
	/*!
	 * Returns the parameters of the neuron
	*/
	NParams getParameters() const;
	/*!
	 * Returns the type of the neuron
	 */
	std::string getType() const; 
    /*!
    It returns  the connections
    */
    std::vector<Connection> getConnections() const;

    void setConnections(const std::vector<Connection> &inhib, const std::vector<Connection> &excit);

    bool isGoingToFire() const;
    void setFiring(bool fire);

    ~Neuron();

private:

    bool willFire;
    bool firing;

    /*! @name Dynamic variables
    */
    ///@{
    double membrane_potential;
    double recovery_variable;
    ///@}
    
    /*! @name Neuron parameters 
    \p a, \p b, \p c, \p d, and the boolean \p inhib if neuron is inhibitory.
    */
    NParams nparams;
    
    std::string type;
    
    /*! @name Connections
      * A vector of connections : \p sender, a pointer to a neuron and \p intensity
    */
    std::vector<Connection> connections;

    size_t n_inhibitory;

};

#endif //NEURON_H
