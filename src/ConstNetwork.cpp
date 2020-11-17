#include "ConstNetwork.h"
#include "Random.h"

ConstNetwork::ConstNetwork(const std::vector<Neuron> &neurons) : Network(neurons) {}

void ConstNetwork::setConnections(double meanIntensity, double meanConnectivity) {
    for(auto& neuron : neurons)
    {
        setNeuronConnections(meanIntensity, meanConnectivity, neuron);
    }
}

void ConstNetwork::setNeuronConnections(double meanIntensity, double meanConnectivity, Neuron &neuron)
{
    for(size_t i(0);i < meanConnectivity ;++i)
    {
        neuron.newConnection({ &neurons[_RNG->uniform_int(0, (int)neurons.size()-1)],
                               _RNG ->uniform_double(0,2*meanIntensity) });
    }
}
