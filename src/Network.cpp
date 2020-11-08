#include "Network.h"
#include "Random.h"


void Network::update()
{
    for(auto neuron : neurons)
        neuron.update();
}

void Network::setConnections(double meanIntensity, double meanConnectivity)
{
    for(auto neuron :neurons)
    {
        int number(_RNG->poisson(meanConnectivity));
        for(int i(0);i<number ;++i)
        {
            neurons[i].newConnection({new Neuron(neurons[_RNG->uniform_int(0, neurons.size())]),
                                      _RNG ->uniform_double(0,2*meanIntensity) });
        }
    }

}





