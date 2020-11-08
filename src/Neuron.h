#ifndef NEURON_H
#define NEURON_H
#include "constants.h"


/*!
 * \class Neuron
  This is a neuron class in which we create neurons. 
  By default a neuron is *RS* type, which is excitatory.
*/

class Neuron;

struct NParams
{
    double a, b, c, d;
    const bool inhib;
};

struct Connection
{
    const Neuron* sender;
    const double intensity;
};

enum Type {RS, FS};

class Neuron
{

public:
    /*!
    The constructor initilize the neuron
    */
    Neuron(Type t);
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
    /*!
    OThe \ref membrane_potential is updated according to the Izhikevich equations.
    */
    void setMembranePotential();
    /*!
    OThe \ref recovery_variable is updated according to the Izhikevich equations.
    */
    void setRecoveryVariable();
    /*!
    A neuron is firing if its membrane potential exceeds the T, the firing treshold, 30 mV
    */
    bool isFiring() const;
    /*!
    Check if a neuron is inhibitory or not
    */
    bool isInhibitor() const;
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

const std::map<Type, NParams> NeuronTypes{
        {Type::RS,  {.02, .2,  -65, 8,   false}},
        {Type::FS,  {.1,  .2,  -65, 2,   true }}
};

#endif //NEURON_H
