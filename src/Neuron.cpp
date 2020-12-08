#include "Neuron.h"
#include "Random.h"
#include "constants.h"
#include <sstream>


Neuron::Neuron(const std::string& type, bool isfiring) :  willFire(false), firing(isfiring), nparams(NeuronTypes.at(type)), type(type), n_inhibitory(0)
{
    membrane_potential = nparams.c;
    recovery_variable = nparams.b*membrane_potential;

    if(type == "RS" or type =="FS")
    {
        double coeff(_RNG->uniform_double(0, 1));
        if (type == "RS")
        {
            nparams.a *= 1 - 0.8 * coeff;
            nparams.b *= 1 + 0.25 * coeff;
        }
        else if(type =="FS")
        {
            coeff *= coeff;
            nparams.c *= 1 - 3. / 13 * coeff;
            nparams.d *= 1 - 0.75 * coeff;
        }
    }
}

double Neuron::currentCalculation()
{
	double current(0);

    for (std::size_t i = 0; i < n_inhibitory; ++i)
        current -= connections[i].intensity * connections[i].sender->isFiring() ;

    for (std::size_t i = n_inhibitory; i < connections.size(); ++i)
        current += connections[i].intensity * 0.5 * connections[i].sender->isFiring();

    int w(isInhibitor() ? 2 : 5);
	return current +  w*_RNG->normal(0,1);
}

void Neuron::update()
{
    if(isFiring())
        reset();

    else
    {
        double potential(membrane_potential);
        setMembranePotential();
        setRecoveryVariable(potential);
    }
    willFire = (membrane_potential > _FIRING_TRESHOLD_);
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

NParams Neuron::getParameters() const
{
	return nparams;
}

std::string Neuron::getType() const
{
	return type;
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

void Neuron::setConnections(const std::vector<Connection> &inhib, const std::vector<Connection> &excit) {
    connections.reserve(inhib.size() + excit.size());
    for (auto & i : inhib)
        connections.emplace_back(i);
    for (auto & i : excit)
        connections.emplace_back(i);
    n_inhibitory = inhib.size();
}

bool Neuron::isGoingToFire() const
{
    return willFire;
}

void Neuron::setFiring(bool fire)
{
    firing = fire;
}

Neuron::~Neuron()
{
    for(auto& c : connections)
        c.sender = nullptr;
}



