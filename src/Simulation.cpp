#include "utility.h"
#include "Simulation.h"
#include "ConstNetwork.h"
#include "DispNetwork.h"
       

Simulation::Simulation(int argc, char **argv) : _props({{"RS", 0}, {"IB", 0}, {"CH", 0}, {"TC", 0},
                                                        {"RZ", 0}, {"FS", 0}, {"LTS", 0}})
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
        std::vector<TCLAP::Arg *> NetworkModels = {&basic, &constant, &overdispersed};
        cmd.xorAdd(NetworkModels);
        cmd.parse(argc, argv);

        int _size = total_n.getValue();
        checkInBound(_NUMBER_TEXT_, _size, _MIN_NEURONS_);
        double _inhib = inhib.getValue();
        checkInBound(_PROP_TEXT_, _inhib, _MIN_PROP_, _MAX_PROP_);
        _endtime = maxt.getValue();
        checkInBound(_TIME_TEXT_, _endtime, _MIN_TIME_);
        double _degree = degree.getValue();
        checkInBound(_CNNCT_TEXT_, _degree, _MIN_CONNECTIVITY_, (double) _size);
        double _strength = strength.getValue();
        checkInBound(_INTENSITY_TEXT_, _strength, _MIN_INTENSITY_);
        _thalamic = thalam.getValue();
        checkInBound(_THALAM_TEXT_, _thalamic, _MIN_THAL_);
        std::string types(typesProp.getValue());
        readTypesProportions(types, inhib.isSet(), _inhib);
        _output = output.getValue();

        if (basic.getValue())
            _net = new Network(_size, _props);
        else if (constant.getValue())
            _net = new ConstNetwork(_size, _props);
        else
            _net = new DispNetwork(_size, _props);
        _net->setConnections(_strength, _degree);


    } catch(TCLAP::ArgException &e)
        {
           set(e.error() + " " + e.argId(), TCLAP_ERROR, true);
        }
}


Simulation::Simulation(const TypesProportions& prop, int size, int endtime, 
					   double degree, double strength, double thalamic,
                       const std::string& output)
: _props(prop), _net(new Network(size, prop)), _endtime(endtime),
  _thalamic(thalamic), _output(output)
{
    _net->setConnections(strength, degree);
}


void Simulation::run(const double time)
{
    std::ofstream outf1, outf2, outf3;
    outf1.open(_output + '_' + _OUTFILE_1_);
    if(outf1.bad())
           set("Cannot write to file " + _output + '_' + _OUTFILE_1_, OUTPUT_ERROR, true);
    
    std::ostream *_outf = &std::cout;
    
    if(outf1.is_open()) _outf = &outf1;
    
    outf2.open(_output + '_' + _OUTFILE_2_);
    if(outf2.bad())
            set("Cannot write to file " + _output + '_' + _OUTFILE_3_, OUTPUT_ERROR, true);

    outf3.open(_output + '_' + _OUTFILE_3_);
    if(outf3.bad())
            set("Cannot write to file " + _output + '_' + _OUTFILE_3_, OUTPUT_ERROR, true);

	sampleHeader(&outf3);	
	
	_net->printParams(&outf2);
    
    for(size_t i(0); i <= time; ++i)
    {
		_net->update(_thalamic);
		(*_outf) << i << ' ';
		_net->printSpikes(_outf);
		(*&outf3) << (i+1) << '\t';
		_net->printSample(&outf3);
    }
	
	if(outf1.is_open()) outf1.close();	
	if(outf2.is_open()) outf2.close();				
	if(outf3.is_open()) outf3.close();
}


void Simulation::sampleHeader(std::ostream *_outstr)
{
	for (const auto& type : _props)
    {
	    if(type.second != 0)
            (*_outstr) <<'\t'<<type.first<<".v" <<'\t'<<type.first<<".u" 
					   <<'\t'<<type.first<<".I";
    }
    (*_outstr) << std::endl;
}


void Simulation::checkMatchingProportions(Iterator beg, Iterator end, const Iterator& def,
                                          bool setDef , double maxSum)
{
    double sum (0);
    for (auto p = beg;  p != end ; p++)
        sum += p->second;
    if(abs(sum - maxSum) <= 0.0001 or (sum - maxSum <= 0.0001 and !setDef))
        def->second += maxSum - sum;
    else
        set("error with type proportions", TCLAP_ERROR, true);
}


void Simulation::readTypesProportions(const std::string& types, bool inhibSet, double inhib)
{
    std::string key, p;
    std::stringstream ss(types);
    while (std::getline(ss, key, ':'))
    {
        key.erase(std::remove_if(key.begin(), key.end(), isspace), key.end());
        std::getline(ss, p, ',');
        if(!p.empty())
            _props.at(key) = stod(p);
    }
    for (const auto& prop : _props)
        checkInBound("The proportions", prop.second, _MIN_PROP_, _MAX_PROP_);

    if(inhibSet)
    {
        TypesProportions propInhib = {{*_props.find("FS")}, {*_props.find("LTS")}};
        checkMatchingProportions(propInhib.begin(), propInhib.end(), propInhib.find("FS"),
                                 types.find("FS") != std::string::npos, inhib);
        _props.at("FS") = propInhib.at("FS");
        _props.at("LTS") = propInhib.at("LTS");
    }
    checkMatchingProportions(_props.begin(), _props.end(), _props.find("RS"),
                             types.find("RS") != std::string::npos, 1);
}


const TypesProportions &Simulation::getProp() const
{
    return _props;
}


Simulation::~Simulation()
{
    delete _net;
    _net = nullptr;
    std::cout.flush();
}
