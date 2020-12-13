#include "DispNetwork.h"
#include "Random.h"

DispNetwork::DispNetwork(const std::vector<Neuron> &neurons) : Network(neurons) {}
DispNetwork::DispNetwork(size_t s, TypesProportions prop) : Network(s, prop) {}

void DispNetwork::setConnections(double meanIntensity, double meanConnectivity)
{
    for(auto& neuron : neurons)
    {
        double connectivity(_RNG->exponential(1/meanConnectivity)); //vérifier que meanConnectivity différent de 0
        Network::setNeuronConnections(meanIntensity, connectivity, neuron);
    }
}
