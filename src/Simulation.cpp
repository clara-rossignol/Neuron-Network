#include "constants.h"
#include "Simulation.h"
#include "Random.h"
#include "Neuron.h"

/// * error handling for TCLAP
/*!
* 0 : "The number of neurons should be between " << _MIN_NEURONS << "and " << _MAX_NEURONS << endl;
* 1 : "The number of steps should be between " << _MIN_TIME_ << "and " << _MAX_TIME_ << endl;
* 2 : "The proportion of excitatory neurons should be between 0 and 1" << endl;
* 3 : "The maximum number of connectivity should be between " << _MIN_CONNECTIVITY_ << "and " << _MAX_CONNECTIVITY_ << endl;
* 4 : "The intensity of a connection should be between " << _MIN_INTENSITY_ << "and " << _MAX_INTENSITY_ << endl;
*/

/* Gestion des erreurs : plusieurs facons de faire :
       / Error::set(type d'erreur, indication d'erreur, code d'erreur)
       / Error::set(type d'erreur + indication d'erreur, code d'erreur) [risque d'être long]
       / Error::set(type d'erreur, code d'erreur) puis cerr << indication d'erreur
       / std::to_string()
       / string("... ")
       /
       */

typedef  std::map<std::string, double>::iterator Iterator ;

Simulation::Simulation(int argc, char **argv)
{
   try {
        TCLAP::CmdLine cmd(_PRGRM_TEXT_);
        TCLAP::ValueArg<int> total_n("N", "neurons", _NUMBER_TEXT_, true, _AVG_NUMBER_, "int");
        cmd.add(total_n);
        TCLAP::ValueArg<int> maxt("t", "time", _TIME_TEXT_, true, _TIME_, "int");
        cmd.add(maxt);
        TCLAP::ValueArg<double> degree("c", "degree", _CNNCT_TEXT_, false, _AVG_CNNCT_, "double");
        cmd.add(degree);
        TCLAP::ValueArg<double> strength("L", "strength", _INTENSITY_TEXT_, false, _AVG_INTENSITY_, "double");
        cmd.add(strength);
        TCLAP::ValueArg<double> pE("p", "excitatory_neurons", _PROP_TEXT_, false, _AVG_PROP_, "double");
        cmd.add(pE);
        TCLAP::ValueArg<std::string> typesProp("T", "neurontypes", _TYPES_TEXT_, false, "", "string");
        cmd.add(typesProp);
        cmd.parse(argc, argv);

        _size = total_n.getValue();
        checkInBound("The number of neurons", _size,_MIN_NEURONS_);
        double _pE = pE.getValue();
        checkInBound("The proportion of excitatory neurons",_pE,_MIN_PE_,_MAX_PE_ );
        _endtime = maxt.getValue();
        checkInBound("The number of steps" , _endtime, _MIN_TIME_);
       _degree = degree.getValue();
        checkInBound("The mean number of connections", _degree, _MIN_CONNECTIVITY_);
       _strength = strength.getValue();
        checkInBound("The mean strength of a connection", _strength, _MIN_INTENSITY_);

        std::string types(typesProp.getValue());
        std::string key, p;
        std::map<std::string, double> prop{{"RS",0}, {"IB",0}, {"CH",0}, {"FS",0}, {"LTS", 0}};

        std::stringstream ss(types);

        while (std::getline(ss, key, ':'))
        {
            std::getline(ss, p, ',');
            prop.at(key) = stoi(p);
        }

        if(pE.isSet())
            checkTypes(prop.find("FS"), prop.find("LTS"), prop.find("LTS"), _pE);
        checkTypes(prop.begin(), prop.end(), prop.find("RS"), 1);

        _net =Network(_size, _pE);
        _net.setConnections(_strength, _degree);
        //faire un switch pour choisir le Network

} catch(TCLAP::ArgException &e) 
{
    throw(TCLAP_ERROR("Error: " + e.error() + " " + e.argId()));
}
catch(std::runtime_error const& e)
{
    // Decision de si on fait qqchose là
}

   
}


void Simulation::run(const double _endtime)
{
    std::ofstream outf1, outf2, outf3;
    outf1.open(outfile+"spikes");
    if(outf1.bad()) 
    throw(OUTPUT_ERROR(std::string("Cannot write to file ")+outfile+"spikes"));
    
    std::ostream *_outf = &std::cout;
    
    if(outf1.is_open()) _outf = &outf1;
    
    outf2.open(outfile+"params");
    if(outf2.bad())
    throw(OUTPUT_ERROR(std::string("Cannot write to file ")+outfile+"params"));
    
    outf3.open(outfile+"sample_neurons");
    if(outf3.bad())
    throw(OUTPUT_ERROR(std::string("Cannot write to file ")+outfile+"sample_neurons"));
    
    for(size_t i(0); i < _endtime; ++i) {
		_net.update();
		_net.print_spikes(_outf);
		(*_outf) << i;
		}
		
	_net.print_params(&outf2);
	if(outf2.is_open()) outf2.close();	
		
			/*
	_net.print_sample(&outf3);*/
	if(outf3.is_open()) outf3.close();
}

Simulation::~Simulation()
{
    std::cout.flush();
}

void Simulation::checkTypes(Iterator beg, Iterator end, const Iterator& def, double max_sum)
{
    double sum (0);
    for (auto p = beg;  p != end ; p++) {
        sum += p->second;
    }
    if(sum <= max_sum and (sum >= max_sum or def->second ==0))
        def->second += max_sum - sum;
    else throw (TCLAP_ERROR(std::string("error with type proportions")));
}


