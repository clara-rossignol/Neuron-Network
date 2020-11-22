#include "constants.h"
#include "Simulation.h"
#include "Random.h"

/// * error handling for TCLAP
/*!
* 0 : "The number of neurons should be between " << _MIN_NEURONS << "and " << _MAX_NEURONS << endl;
* 1 : "The number of steps should be between " << _MIN_TIME_ << "and " << _MAX_TIME_ << endl;
* 2 : "The proportion of excitatory neurons should be between 0 and 1" << endl;
* 3 : "The maximum number of connectivity should be between " << _MIN_CONNECTIVITY_ << "and " << _MAX_CONNECTIVITY_ << endl;
* 4 : "The intensity of a connection should be between " << _MIN_INTENSITY_ << "and " << _MAX_INTENSITY_ << endl;
*/

Simulation::Simulation(int argc, char **argv) {
   try {
        TCLAP::CmdLine cmd(_PRGRM_TEXT_);
        TCLAP::ValueArg<int> total_n("N", "neurons", _NUMBER_TEXT_, false, _AVG_NUMBER_, "int");
            
        cmd.add(total_n);
        TCLAP::ValueArg<double> pE("p", "excitatory_neurons", _PROP_TEXT_, false, _AVG_PROP_, "double");
        cmd.add(pE);
        TCLAP::ValueArg<int> maxt("t", "time", _TIME_TEXT_, false, _TIME_, "int");
        cmd.add(maxt);
        TCLAP::ValueArg<double> connectivity("c", "connectivity", _CNNCT_TEXT_, false, _AVG_CNNCT_, "double");        
        cmd.add(connectivity);
        TCLAP::ValueArg<double> intensity("L", "intensity", _INTENSITY_TEXT_, false, _AVG_INTENSITY_, "double");
        cmd.add(intensity);
        
        TCLAP::ValueArg<std::string> ofile("o", "outptut", _OUTPUT_TEXT_, false, "", "string");
        cmd.add(ofile);
        //add different types of neurons
        /* */
        TCLAP::ValueArg<std::string> typesArg("T", "neurontypes", _TYPES_TEXT_,  false, "", "string");
        cmd.add(typesArg);
        
        //not sure if this is needed
        TCLAP::ValueArg<long> seed("S", "seed", "Random seed", false, 0, "long");
        cmd.add(seed);
        cmd.parse(argc, argv);

        if (total_n.getValue() > _MAX_NEURONS_ || total_n.getValue() < _MIN_NEURONS_)
        {
            Error::set("Invalid data entered", 1);
            std::cerr << "The number of neurons should be between " << _MIN_NEURONS_ << "and " << _MAX_NEURONS_ << std::endl;
        }

        if (pE.getValue() < 0 || pE.getValue() > 1)
        {
            Error::set("Invalid data entered", 1);
            std::cerr << "The proportion of excitatory neurons should be between 0 and 1" << std::endl;
        }
        
        if ((maxt.getValue() < _MIN_TIME_) || (maxt.getValue() > _MAX_TIME_))
        {
            Error::set("Invalid data entered", 1);
            std::cerr << "The number of steps should be between " << _MIN_TIME_ << "and " << _MAX_TIME_ << std::endl;
        }

        if (connectivity.getValue() < _MIN_CONNECTIVITY_ || connectivity.getValue() > _MAX_CONNECTIVITY_)
        {
            Error::set("Invalid data entered", 1);
            std::cerr << "The maximum number of connectivity should be between " << _MIN_CONNECTIVITY_ << "and " << _MAX_CONNECTIVITY_ << std::endl;
        }
        
        if (intensity.getValue() < _MIN_INTENSITY_ || intensity.getValue() > _MAX_INTENSITY_)
        {
            Error::set("Invalid data entered", 1);
            std::cerr << "The intensity of a connection should be between " << _MIN_INTENSITY_ << "and " << _MAX_INTENSITY_ << std::endl;
        }


        /* Gestion des erreurs : plusieurs facons de faire :
        / Error::set(type d'erreur, indication d'erreur, code d'erreur)
        / Error::set(type d'erreur + indication d'erreur, code d'erreur) [risque d'être long]
        / Error::set(type d'erreur, code d'erreur) puis cerr << indication d'erreur
        / std::to_string()
        / string("... ")
        /
        */
        
        _size = total_n.getValue();
        _pE = pE.getValue();
        _endtime = maxt.getValue();
        _connectivity = connectivity.getValue();
        _intensity = intensity.getValue();
        
        std::string outfname = ofile.getValue();
        std::string types(typesArg.getValue());
        
        _net = Network(_size, _pE);
        _net.setConnections(_intensity, _connectivity);
 
        
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


