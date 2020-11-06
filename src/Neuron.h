#ifndef NEURON_H
#define NEURON_H

#include "constants.h"

/*!
  This is a neuron class.
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


class Neuron {


public:
    Neuron(Type t);
    void newConnection(const Connection& connection);
    double currentCalculation();
    void update();
    void reset();
    void setMembranePotential();
    void setRecoveryVariable();
    bool isFiring() const;
    bool isInhibitor() const;
    ~Neuron();

private:
    bool firing;
    double membrane_potential;
    double recovery_variable;
    NParams nparams;
    std::vector<Connection> connections;

};

const std::map<Type, NParams> NeuronTypes{
        {Type::RS,  {.02, .2,  -65, 8,   false}},
        {Type::FS,  {.1,  .2,  -65, 2,   true }}
};

#endif //NEURON_H
