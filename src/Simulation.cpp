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
       
static int nFS, nRS;

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
        TCLAP::ValueArg<std::string> output("o", "output_files_name", _OUT_TEXT_, false, _AVG_OUT_, "string");
        cmd.add(output);
        TCLAP::ValueArg<double> thalam("l", "thalamic_input", _THALAM_TEXT_, false, _AVG_THAL_, "double");
        cmd.add(thalam);
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
        checkInBound(_CNNCT_TEXT_, _degree, _MIN_CONNECTIVITY_, (double)_size);
       _strength = strength.getValue();
        checkInBound(_INTENSITY_TEXT_, _strength, _MIN_INTENSITY_);
        _output = output.getValue();
        _thalamic = thalam.getValue();
        checkInBound(_THALAM_TEXT_, _thalamic, _MIN_THALAM_, _MAX_THALAM_);
        std::string types(typesProp.getValue());
        
        if(basic.getValue())
            _net = new Network(_size, readTypesProportions(types, inhib.isSet(), _inhib));
        else if (constant.getValue())
            _net = new ConstNetwork(_size, readTypesProportions(types, inhib.isSet(), _inhib));
        else
            _net = new DispNetwork(_size, readTypesProportions(types, inhib.isSet(), _inhib));

        _net->setConnections(_strength, _degree);
        
        TypesProportions props = readTypesProportions(types, inhib.isSet(), _inhib);
        //neurons who will be followed in sample_neurons
        nFS = ((props.at("CH")*_size) + 1);
        nRS = ((props.at("CH")*_size) + (props.at("FS")*_size) + (props.at("IB")*_size) + (props.at("LTS")*_size) + 1);


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
    outf1.open(_output + '_' + _OUTFILE_1_);
    if(outf1.bad()) 
        throw(OUTPUT_ERROR(std::string("Cannot write to file ") + _output + '_' +_OUTFILE_1_));
    
    std::ostream *_outf = &std::cout;
    
    if(outf1.is_open()) _outf = &outf1;
    
    outf2.open(_output + '_' + _OUTFILE_2_);
    if(outf2.bad())
        throw(OUTPUT_ERROR(std::string("Cannot write to file ") + _output + '_' + _OUTFILE_2_));
    
    outf3.open(_output + '_' + _OUTFILE_3_);
    if(outf3.bad())
    {
        throw(OUTPUT_ERROR(std::string("Cannot write to file ") + _output + '_' + _OUTFILE_3_));
	}

	sample_header(&outf3);	
	
	_net->print_params(&outf2);
    
    for(size_t i(0); i < _time; ++i) {
		_net->update();
		(*_outf) << i << ' ';
		_net->print_spikes(_outf);
		(*&outf3) << (i+1) << '\t';
		_net->print_sample(&outf3, nFS, nRS);
		}
	
	if(outf1.is_open()) outf1.close();	
	if(outf2.is_open()) outf2.close();				
	if(outf3.is_open()) outf3.close();
}

void Simulation::sample_header(std::ostream *_outstr) {
	(*_outstr) << "\tFS.v\tFS.u\tFS.I\tRS.v\tRS.u\tRS.I" << std::endl;
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
