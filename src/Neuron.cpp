#include "Neuron.h"
#include "Random.h"
#include "constants.h"
#include <sstream>


Neuron::Neuron(const std::string& type, bool isfiring) : _willFire(false),_firing(isfiring), _current(0), _nparams(NeuronTypes.at(type)),_type(type), _nInhibitory(0)
{
    _membranePotential = _nparams.c;
    _recoveryVariable = _nparams.b*_membranePotential;

    if (_type == "FS")
    {
        double coeff(_RNG->uniform_double(0, 1));
        _nparams.a *= 1 - 0.8 * coeff;
        _nparams.b *= 1 + 0.25 * coeff;
    }
    else if(_type =="RS")
    {
        double coeff(_RNG->uniform_double(0, 1));
        coeff *= coeff;
        _nparams.c *= 1 - 3. / 13 * coeff;
        _nparams.d *= 1 - 0.75 * coeff;
    }
}

void Neuron::currentCalculation(double thal)
{
	double input(0);

    for (std::size_t i = 0; i < _nInhibitory; ++i)
        input -= _connections[i].intensity * _connections[i].sender->isFiring() ;

    for (std::size_t i(_nInhibitory); i < _connections.size(); ++i)
        input += _connections[i].intensity * 0.5 * _connections[i].sender->isFiring();

    int w(isInhibitor() ? 2 : 5);
	_current =  input +  w*_RNG->normal(0,thal);
}

void Neuron::update(double thal)
{
    if(isFiring())
        reset();

    else
    {
		currentCalculation(thal);
        double potential(_membranePotential);
        setMembranePotential();
        setRecoveryVariable(potential);
    }
    _willFire = (_membranePotential > _FIRING_TRESHOLD_);
}

void Neuron::reset()
{
    _membranePotential=_nparams.c;
    _recoveryVariable+=_nparams.d;
}

void Neuron::setMembranePotential()
{
    _membranePotential += (0.04*pow(_membranePotential, 2) + 5*_membranePotential + 140 - _recoveryVariable + _current)*_DELTA_MBRN_;
}
void Neuron::setRecoveryVariable(double potential)
{
    _recoveryVariable += (_nparams.a*(_nparams.b*potential - _recoveryVariable))*_DELTA_RECV_;
}

bool Neuron::isFiring() const
{
    return _firing;
}

bool Neuron::isInhibitor() const
{
    return _nparams.inhib;
}

NParams Neuron::getParameters() const
{
	return _nparams;
}

std::string Neuron::getType() const
{
	return _type;
}

double Neuron::getMembranePotential() const
{
    return _membranePotential;
}

double Neuron::getRecoveryVariable() const
{
    return _recoveryVariable;
}

std::vector<Connection> Neuron::getConnections() const
{
    return _connections;
}

void Neuron::setConnections(const std::vector<Connection> &inhib, const std::vector<Connection> &excit)
{
    _connections.reserve(inhib.size() + excit.size());
    for (auto & i : inhib)
        _connections.emplace_back(i);
    for (auto & i : excit)
        _connections.emplace_back(i);
    _nInhibitory = inhib.size();
}

bool Neuron::isGoingToFire() const
{
    return _willFire;
}

void Neuron::setFiring(bool fire)
{
    _firing = fire;
}

size_t Neuron::getNInhibitory() const
{
    return _nInhibitory;
}

double Neuron::getCurrent() const
{
    return _current;
}

Neuron::~Neuron()
{
    for(auto& c : _connections)
        c.sender = nullptr;
}
