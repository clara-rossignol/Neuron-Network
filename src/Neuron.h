#ifndef NEURON_H
#define NEURON_H
#include "constants.h"


/*!
 * \class Neuron
  This is a neuron class in which we create neurons.
  A neuron is defined by 4 parameters \p a, \p b, \p c, \p d and its inhibitory or excitatory quality.
*/

class Neuron
{

public:
    /*!
    The constructor initializes the neuron
    */
    Neuron(Type t, bool isfiring = false);
    
    void newConnection(const Connection& connection);
    
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
	/*! \ref membrane_potential getter
	*/
	double getMembranePotential() const;
	/*! \ref recovery_variable getter
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

    std::vector<Connection> getConnections() const;

    ~Neuron();

private:
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
    
     /*! @name Connections
      * A vector of connections : \p sender, a pointer to a neuron and \p intensity
    */
    std::vector<Connection> connections;

};

#endif //NEURON_H
