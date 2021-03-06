#include "Network.h"
#include "Random.h"
#include <sstream>

Network::Network(size_t size, const TypesProportions& prop)
{
   size_t index(0);
   for(const auto& type : prop)
   {
       size_t numType (size * type.second);
       if(numType)
       {
           index += numType;
           indexes.push_back(index);
       }

       for(size_t i(0); i<numType; ++i)
           neurons.emplace_back(type.first);
   }
}

void Network::update(double thal)
{
    for(auto& neuron : neurons)
        neuron.update(thal);
    for(auto& neuron : neurons)
        neuron.setFiring(neuron.isGoingToFire());
}

void Network::setConnections(double meanIntensity,
double meanConnectivity)
{
    for(auto& neuron : neurons)
        setNeuronConnections(meanIntensity, meanConnectivity, neuron);
}

void Network::setNeuronConnections(double meanIntensity, double meanConnectivity, Neuron& neuron)
{
    int number(-1);
    while (number < 0 or number > (int)neurons.size())
        number = _RNG->poisson(meanConnectivity);

    // By separating the neurons between inhibitory and excitatory ones we can
    // speed up significantly the method current_calculation in Neuron
    std::vector<Connection> inhib;
    std::vector<Connection> excit;
    for(size_t i(0);i < (size_t)number ;++i)
    {
        Neuron* sender = &neurons[_RNG->uniform_int(0, (int)neurons.size()-1)];
        if (sender->isInhibitor())
            inhib.push_back({sender, _RNG ->uniform_double(0,2*meanIntensity) });
        else
            excit.push_back({sender, _RNG ->uniform_double(0,2*meanIntensity) });
    }
    neuron.setConnections(inhib, excit);
}


void Network::printParams(std::ostream *_outstr)
{
    (*_outstr) << "Type\ta\tb\tc\td\tInhibitory\tdegree\tvalence" << std::endl;
    for (auto & neuron : neurons)
    {
		double valence(0);
		for (size_t i(0); i<neuron.getNInhibitory(); ++i)
				valence -= neuron.getConnections()[i].intensity;
		for (size_t i(neuron.getNInhibitory()); i<neuron.getConnections().size(); ++i)
				valence += neuron.getConnections()[i].intensity;

		std::stringstream ss;
		ss << neuron.getType() << '\t'
		   << neuron.getParameters().a << '\t'
		   << neuron.getParameters().b << '\t'
		   << neuron.getParameters().c << '\t'
		   << neuron.getParameters().d << '\t'
		   << neuron.getParameters().inhib << '\t'
		   << neuron.getConnections().size() << '\t'
		   << valence;
        (*_outstr) 	<< ss.str()
					<< std::endl;
    }
}

void Network::printSample(std::ostream *_outstr)
{
	std::stringstream ss;
	for(auto index = indexes.begin(); index < indexes.end()-1; ++index)
    {
	    ss << neurons[*index-1].getMembranePotential() << '\t'
	       << neurons[*index-1].getRecoveryVariable() << '\t'
	       << neurons[*index-1].getCurrent() << '\t';
    }
    ss << neurons[*(indexes.end()-1)-1].getMembranePotential() << '\t'
       << neurons[*(indexes.end()-1)-1].getRecoveryVariable() << '\t'
       << neurons[*(indexes.end()-1)-1].getCurrent();

	(*_outstr) 	<< ss.str()
				<< std::endl;
}


void Network::printSpikes(std::ostream *_outstr)
{
	for(auto & neuron : neurons)
		(*_outstr)  << neuron.isFiring() << ' ';
	(*_outstr) << std::endl;
}

const std::vector<Neuron> &Network::getNeurons() const
{
    return neurons;
}

const std::vector<int> &Network::getIndexes() const
{
	return indexes;
}
