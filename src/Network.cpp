#include "Network.h"
#include "Random.h"
#include <sstream>

Network::Network(const std::vector<Neuron>& neurons) : neurons(neurons){}

Network::Network(size_t s, const TypesProportions& prop)
{
   for(const auto& type : prop)
   {
       for(size_t i(0); i<s*type.second; ++i)
           neurons.emplace_back(type.first);
   }
}

void Network::update()
{
    for(auto& neuron : neurons)
        neuron.update();
    for(auto& neuron : neurons)
        neuron.setFiring(neuron.isGoingToFire());
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

    std::vector<Connection> inhib;
    std::vector<Connection> excit;
    for(size_t i(0);i < (unsigned int)number ;++i)
    {
        Neuron* sender = &neurons[_RNG->uniform_int(0, (int)neurons.size()-1)];
        if (sender->isInhibitor())
            inhib.push_back({sender, _RNG ->uniform_double(0,2*meanIntensity) });
        else
            excit.push_back({sender, _RNG ->uniform_double(0,2*meanIntensity) });
    }

    neuron.setConnections(inhib, excit);

}


void Network::print_params(std::ostream *_outstr) {
    (*_outstr) << "Type\ta\tb\tc\td\tInhibitory\tdegree\tvalence" << std::endl;
    for (auto & neuron : neurons) {
		double valence(0);
		for (auto connect : neuron.getConnections())
		{
			valence += connect.intensity;
			}
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


void Network::print_sample(std::ostream *_outstr, size_t nFS, size_t nRS) {
	std::stringstream ss;
	ss 	<< neurons[nFS].getMembranePotential() << '\t'
		<< neurons[nFS].getRecoveryVariable() << '\t'
		<< neurons[nFS].currentCalculation() << '\t'
		<< neurons[nRS].getMembranePotential() << '\t'
		<< neurons[nRS].getRecoveryVariable() << '\t'
		<< neurons[nRS].currentCalculation();
	(*_outstr) 	<< ss.str()	 
				<< std::endl;	
}


void Network::print_spikes(std::ostream *_outstr) {
	for(auto & neuron : neurons) {
		(*_outstr)  << neuron.isFiring() << ' ';
}
		(*_outstr) << std::endl;
}

const std::vector<Neuron> &Network::getNeurons() const
{
    return neurons;
}










