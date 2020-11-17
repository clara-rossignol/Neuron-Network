#include "Neuron.h"
#include "Random.h"
#include "constants.h"


Neuron::Neuron(Type t, bool isfiring) : firing(isfiring),  nparams(NeuronTypes.at(t))
{
    membrane_potential = nparams.c;
    recovery_variable = nparams.b*membrane_potential;

    if(t==RS or t==FS)
    {
        double coeff(_RNG->uniform_double(0, 1));
        if (NeuronTypes.at(t).inhib)
        {
            nparams.a *= 1 - 0.8 * coeff;
            nparams.b *= 1 + 0.25 * coeff;
        }
        else
        {
            coeff *= coeff;
            nparams.c *= 1 - 3. / 13 * coeff;
            nparams.d *= 1 - 0.75 * coeff;
        }
    }
}

void Neuron::newConnection(const Connection & c)
{
    connections.push_back(c);
}

double Neuron::currentCalculation()
{
	double current(0);
	for(const auto& c : connections) //maybe a better way to optimize it
    {
	    if(c.sender->isInhibitor())
            current -=c.intensity;
	    else
            current +=c.intensity*0.5;
    }
    int w(isInhibitor() ? 2 : 5);
	return current +  w*_RNG->normal(0,1);
}

void Neuron::update()
{
    if(isFiring()) {
        reset();
}
    else
    {
        double potential(membrane_potential);
        setMembranePotential();
        setRecoveryVariable(potential);
        firing = (membrane_potential > _FIRING_TRESHOLD_);
    }
}

void Neuron::reset()
{
    membrane_potential=nparams.c;
    recovery_variable+=nparams.d;
}

void Neuron::setMembranePotential()
{
    membrane_potential += (0.04*pow(membrane_potential, 2) + 5*membrane_potential + 140 - recovery_variable + currentCalculation())*_DELTA_MBRN_;
}
void Neuron::setRecoveryVariable(double potential)
{
    recovery_variable += (nparams.a*(nparams.b*potential - recovery_variable))*_DELTA_RECV_;
}

bool Neuron::isFiring() const
{
    return firing;
}

bool Neuron::isInhibitor() const
{
    return nparams.inhib;
}

double Neuron::getMembranePotential() const
{
    return membrane_potential;
}

double Neuron::getRecoveryVariable() const
{
    return recovery_variable;
}

std::vector<Connection> Neuron::getConnections() const
{
    return connections;
}

Neuron::~Neuron()
{
    for(auto& c : connections)
    {
        c.sender = nullptr;
    }
}


