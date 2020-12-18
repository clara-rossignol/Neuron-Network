#include "Neuron.h"
#include "Random.h"
#include "utility.h"
#include <sstream>


Neuron::Neuron(const std::string& type, bool isFiring) : willFire(false),
firing(isFiring), current(0), nParams(NeuronTypes.at(type)),type(type), 
nInhibitory(0)
{
    
    membranePotential = _INIT_POT_;

    if (type == "FS")
    {
        const double coeff(_RNG->uniform_double(0, 1));
        nParams.a *= 1 - 0.8 * coeff;
        nParams.b *= 1 + 0.25 * coeff;
    }
    else if(type =="RS")
    {
        const double coeff(pow(_RNG->uniform_double(0, 1), 2));
        nParams.c *= 1 - 3. / 13 * coeff;
        nParams.d *= 1 - 0.75 * coeff;
    }
    recoveryVariable = nParams.b * membranePotential;
}

void Neuron::currentCalculation(double thal)
{
	double input(0);

    for (std::size_t i = 0; i < nInhibitory; ++i)
        input -= connections[i].intensity
				*connections[i].sender->isFiring() ;

    for (std::size_t i(nInhibitory); i < connections.size(); ++i)
        input += connections[i].intensity*0.5
				*connections[i].sender->isFiring();

    int w(isInhibitor() ? 2 : 5);
	current =  input +  w*_RNG->normal(0,thal);
}

void Neuron::update(double thal)
{
    if(isFiring())
        reset();
    else
    {
		currentCalculation(thal);
        const double potential(membranePotential);
        setMembranePotential();
        setRecoveryVariable(potential);
    }
    willFire = (membranePotential > _FIRING_TRESHOLD_);
}

void Neuron::reset()
{
    membranePotential=nParams.c;
    recoveryVariable+=nParams.d;
}

void Neuron::setMembranePotential()
{
    membranePotential += (0.04*pow(membranePotential, 2) 
						+ 5*membranePotential + 140 - recoveryVariable 
						+ current)*_DELTA_MBRN_;
}

void Neuron::setRecoveryVariable(double potential)
{
    recoveryVariable += (nParams.a*(nParams.b*potential - recoveryVariable))*_DELTA_RECV_;
}

bool Neuron::isFiring() const
{
    return firing;
}

bool Neuron::isInhibitor() const
{
    return nParams.inhib;
}

NParams Neuron::getParameters() const
{
	return nParams;
}

std::string Neuron::getType() const
{
	return type;
}

double Neuron::getMembranePotential() const
{
    return membranePotential;
}

double Neuron::getRecoveryVariable() const
{
    return recoveryVariable;
}

std::vector<Connection> Neuron::getConnections() const
{
    return connections;
}

void Neuron::setConnections(const std::vector<Connection> &inhib, 
const std::vector<Connection> &excit)
{
    connections.reserve(inhib.size() + excit.size());
    for (auto & i : inhib)
        connections.emplace_back(i);
    for (auto & i : excit)
        connections.emplace_back(i);
    nInhibitory = inhib.size();
}

bool Neuron::isGoingToFire() const
{
    return willFire;
}

void Neuron::setFiring(bool fire)
{
    firing = fire;
}

size_t Neuron::getNInhibitory() const
{
    return nInhibitory;
}

double Neuron::getCurrent() const
{
    return current;
}

Neuron::~Neuron()
{
    for(auto& c : connections)
        c.sender = nullptr;
}
