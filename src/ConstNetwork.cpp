#include "ConstNetwork.h"
#include "Random.h"

ConstNetwork::ConstNetwork(const std::vector<Neuron> &neurons) : Network(neurons) {}
ConstNetwork::ConstNetwork(size_t s, TypesProportions prop) : Network(s, prop) {}

void ConstNetwork::setConnections(double meanIntensity, double meanConnectivity) 
{
    for(auto& neuron : neurons)
    {
        setNeuronConnections(meanIntensity, meanConnectivity, neuron);
    }
}

void ConstNetwork::setNeuronConnections(double meanIntensity, 
double meanConnectivity, Neuron &neuron)
{
    std::vector<Connection> inhib;
    std::vector<Connection> excit;

    for(size_t i(0);i < meanConnectivity;++i)
    {
        Neuron* sender = &neurons[_RNG->uniform_int(0, (int)neurons.size()-1)];
        if (sender->isInhibitor())
            inhib.push_back({sender, _RNG ->uniform_double(0,2*meanIntensity)  });
        else
            excit.push_back({sender, _RNG ->uniform_double(0,2*meanIntensity) });
    }
    neuron.setConnections(inhib, excit);
}
