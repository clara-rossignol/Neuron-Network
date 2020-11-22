#include "Network.h"
#include "Random.h"

Network::Network(const std::vector<Neuron>& neurons) : neurons(neurons){}

Network::Network(size_t s, double pE) {
	for(size_t i(0); i < s; ++i) {
		if(i < (s*pE)){
			neurons.push_back(Neuron(RS));
			} else {
				neurons.push_back(Neuron(FS));
			}
	}
}
	

void Network::update()
{
    for(auto& neuron : neurons)
        neuron.update();
}

void Network::setConnections(double meanIntensity, double meanConnectivity)
{
    for(auto& neuron :neurons)
        setNeuronConnections(meanIntensity, meanConnectivity, neuron);
}

void Network::setNeuronConnections(double meanIntensity, double meanConnectivity, Neuron& neuron)
{
    int number(-1);
    while (number < 0 or number > (int)neurons.size())
        number = _RNG->poisson(meanConnectivity);

    for(size_t i(0);i < (unsigned int)number ;++i)
    {
        neuron.newConnection({ &neurons[_RNG->uniform_int(0, (int)neurons.size()-1)],
                               _RNG ->uniform_double(0,2*meanIntensity) });
    }
}

const std::vector<Neuron> &Network::getNeurons() const
{
    return neurons;
}








