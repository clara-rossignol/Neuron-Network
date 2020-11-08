#include "Neuron.h"
#include "Random.h"
#include <cmath>

Neuron::Neuron(Type t) : firing(false),  nparams(NeuronTypes.at(t))
{
    membrane_potential = nparams.c;
    recovery_variable = nparams.b*membrane_potential;

    double coeff(_RNG->uniform_double(0,1));
    if (NeuronTypes.at(t).inhib)
    {
        nparams.a *= 1-0.8*coeff; //maybe make them constants in constants.h
        nparams.b *= 1+0.25*coeff;
    }
    else
    {
        coeff *= coeff;
        nparams.c *= 1 - 3. / 13 * coeff;
        nparams.d *= 1 - 0.75 * coeff;
    }
}

void Neuron::newConnection(const Connection & c)
{
    connections.push_back(c);
}


double Neuron::currentCalculation()
{
	double current(0);
	for(auto c : connections)
    {
	    if(c.sender->isInhibitor())
            current -=c.intensity;
	    else
            current +=c.intensity*0.5;
    }
    int w(isInhibitor() ? 2 : 5);
	return current +w*_RNG->normal(0,1);
}

void Neuron::update()
{
    firing = membrane_potential>30;
    if(isFiring())
        reset();
    else
    {
        setMembranePotential();
        setRecoveryVariable();
    }
}

void Neuron::reset()
{
    membrane_potential=nparams.c;
    recovery_variable+=nparams.d;
}

void Neuron::setMembranePotential()
{
    membrane_potential += (0.04*pow(membrane_potential, 2) + 5*membrane_potential + 140 - recovery_variable +
                           currentCalculation())*1; //define constants ?
}
void Neuron::setRecoveryVariable()
{
    recovery_variable += nparams.a*(nparams.b*membrane_potential - recovery_variable)*0.5; //define constants ?
}

bool Neuron::isFiring() const
{
    return firing;
}

bool Neuron::isInhibitor() const
{
    return nparams.inhib;
}

Neuron::~Neuron()
{
    for(auto c : connections)
    {
        delete c.sender;
        c.sender = nullptr;
    }
}





