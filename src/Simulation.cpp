#include "constants.h"
#include "Simulation.h"
#include "Random.h"
#include "Neuron.h"
#include "ConstNetwork.h"
#include "DispNetwork.h"

///
/* Gestion des erreurs : plusieurs facons de faire :
       / Error::set(type d'erreur, indication d'erreur, code d'erreur)
       / Error::set(type d'erreur + indication d'erreur, code d'erreur) [risque d'être long]
       / Error::set(type d'erreur, code d'erreur) puis cerr << indication d'erreur
       / std::to_string()
       / string("... ")
       /
       */


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
        TCLAP::ValueArg<double> inhib("i", "inhibitory_neurons", _PROP_TEXT_, false, _AVG_PROP_, "double");
        cmd.add(inhib);
        TCLAP::ValueArg<std::string> typesProp("T", "neurontypes", _TYPES_TEXT_, true, "", "string");
        cmd.add(typesProp);
        TCLAP::SwitchArg basic("B", "basic", _BASIC_TEXT_, false);
        TCLAP::SwitchArg constant("C", "constant", _CONSTANT_TEXT, false);
        TCLAP::SwitchArg overdispersed("O", "overdispersed", _OVERDISPERSED_TEXT, false);
        std::vector< TCLAP::Arg *> NetworkModels = {&basic, &constant, &overdispersed};
        cmd.xorAdd(NetworkModels);
        cmd.parse(argc, argv);

        _size = total_n.getValue();
        checkInBound(_NUMBER_TEXT_, _size,_MIN_NEURONS_);
        double _inhib = inhib.getValue();
        checkInBound(_PROP_TEXT_, _inhib, _MIN_PE_, _MAX_PE_ );
        _endtime = maxt.getValue();
        checkInBound(_TIME_TEXT_ , _endtime, _MIN_TIME_);
       _degree = degree.getValue();
        checkInBound(_CNNCT_TEXT_, _degree, _MIN_CONNECTIVITY_);
       _strength = strength.getValue();
        checkInBound(_INTENSITY_TEXT_, _strength, _MIN_INTENSITY_);
        std::string types(typesProp.getValue());

        if(basic.getValue())
            _net = new Network(_size, readTypesProportions(types, inhib.isSet(), _inhib));
        else if (constant.getValue())
            _net = new ConstNetwork(_size, readTypesProportions(types, inhib.isSet(), _inhib));
        else
            _net = new DispNetwork(_size, readTypesProportions(types, inhib.isSet(), _inhib));

        _net->setConnections(_strength, _degree);

} catch(TCLAP::ArgException &e) 
{
    throw(TCLAP_ERROR("Error: " + e.error() + " " + e.argId()));
}
catch(std::runtime_error const& e)
{
    // Decision de si on fait qqchose là
}

   
}


void Simulation::run(const double _time)
{
    std::ofstream outf1, outf2, outf3;
    outf1.open(_OUTFILE_1_);
    if(outf1.bad()) 
        throw(OUTPUT_ERROR(std::string("Cannot write to file ")+_OUTFILE_1_));
    
    std::ostream *_outf = &std::cout;
    
    if(outf1.is_open()) _outf = &outf1;
    
    outf2.open(_OUTFILE_2_);
    if(outf2.bad())
        throw(OUTPUT_ERROR(std::string("Cannot write to file ")+_OUTFILE_2_));
    
    outf3.open(_OUTFILE_3_);
    if(outf3.bad())
        throw(OUTPUT_ERROR(std::string("Cannot write to file ")+_OUTFILE_3_));

	sample_header(&outf3);
	int num(_RNG->uniform_int(0, _size));
    
    for(size_t i(0); i < _time; ++i) {
		_net->update();
		_net->print_spikes(_outf);
		(*_outf) << i << ' ';
		(*&outf3) << (i+1) << '\t';
		_net->print_sample(&outf3, num);
		}
		
	_net->print_params(&outf2);
	
	if(outf1.is_open()) outf1.close();	
	if(outf2.is_open()) outf2.close();				
	if(outf3.is_open()) outf3.close();
}

void Simulation::sample_header(std::ostream *_outstr) {
	(*_outstr) << "\t\tv\tu\tI" << std::endl;
}

void Simulation::checkTypes(Iterator beg, Iterator end, const Iterator& def, bool setDef ,double max_sum)
{
    double sum (0);
    for (auto p = beg;  p != end ; p++) {
        sum += p->second;
    }
    if(abs(sum - max_sum) <= 0.0001  or  (sum - max_sum <= 0.0001 and !setDef))
        def->second += max_sum - sum;
    else
    {
       throw (TCLAP_ERROR(std::string("error with type proportions")));
       //throw;
    }
}

TypesProportions Simulation::readTypesProportions(const std::string& types, bool inhibSet, double inhib)
{
    std::string key, p;
    TypesProportions prop{{"RS",0}, {"IB",0}, {"CH",0},{"TC",0}, {"RZ",0}, {"FS",0},  {"LTS", 0}};
    std::stringstream ss(types);

    while (std::getline(ss, key, ':'))
    {
        std::getline(ss, p, ',');
        prop.at(key) = stod(p);
    }

    if(inhibSet)
        checkTypes(prop.find("FS"), prop.find("LTS"), prop.find("FS"), types.find("FS") != std::string::npos, inhib);
    checkTypes(prop.begin(), prop.end(), prop.find("RS"),types.find("RS") != std::string::npos,1);
    return prop;
}

Simulation::~Simulation()
{
    delete _net;
    _net = nullptr;
    std::cout.flush();
}
