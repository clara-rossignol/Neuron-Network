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
            // if (total_n > _MAX_TIME_ || total_n < _MIN_TIME_) throw 0;
        cmd.add(total_n);
        TCLAP::ValueArg<double> pE("p", "excitatory_neurons", _PROP_TEXT_, false, _AVG_PROP_, "double");
        //here I got an error: Argument flag can only be one character long Argument. That is why I changed pE to p.
            // if (pE < 0 || pE > 1) throw 2;
        cmd.add(pE);
        TCLAP::ValueArg<int> maxt("t", "time", _TIME_TEXT_, false, _TIME_, "int");
            // if (maxt < _MIN_TIME_ || maxt > _MAX_TIME_) throw 1;
        cmd.add(maxt);
        TCLAP::ValueArg<double> connectivity("c", "connectivity", _CNNCT_TEXT_, false, _AVG_CNNCT_, "double");
        //here i got the same error that is why I changed it to c.
            // if (connectivity < _MIN_CONNECTIVITY_ || connectivity > _MAX_CONNECTIVITY_) throw 3;         
        cmd.add(connectivity);
        TCLAP::ValueArg<double> intensity("L", "intensity", _INTENSITY_TEXT_, false, _AVG_INTENSITY_, "double");
            // if (intensity < _MIN_INTENSITY_ || intensity > _MAX_INTENSITY_) throw 4;
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
        //not sure if this is needed
        _RNG = new RandomNumbers(seed.getValue());
        
        _size = total_n.getValue();
        _pE = pE.getValue();
        _endtime = maxt.getValue();
        _connectivity = connectivity.getValue();
        _intensity = intensity.getValue();
        std::string outfname = ofile.getValue();
        if (outfname.length()) outfile.open(outfname, std::ios_base::out);
        std::string types(typesArg.getValue());
        
} catch(TCLAP::ArgException &e) {
        throw(TCLAP_ERROR("Error: " + e.error() + " " + e.argId()));
    }
/*catch(int n){
   How to manage the error without if loop that could slow the program ?   
  }
*/ 
   
}

void Simulation::run(const double _endtime){
    this->header();

    for (size_t i(0); i < _endtime; ++i) { // il faudra changer ća car comparaison size_t et double
        //_net.update();
        this->print();
    }
}

void Simulation::header() {
    std::ostream *outstr = &std::cout;
    if (outfile.is_open()) outstr = &outfile;
    *outstr << "Type";
        *outstr << "\ta" << "\tb" << "\tc" << "\td"<< "\tInhibitory"<< "\tdegree "<<"\tvalence";
    *outstr << std::endl;
}
void Simulation::print() {
  
    //here I have to add the parameters of a neuron type: a,b,c,d; maybe we can make a method get_params in neuron, so we print them
    std::ostream *outstr = &std::cout;
    if (outfile.is_open()) outstr = &outfile;
    //for (auto n : neurons) 
       // *outstr << "\t" << n->get_params(); 
    *outstr << std::endl;
}

Simulation::~Simulation() {
    if(outfile.is_open())
    outfile.close();
    std::cout.flush();
}

/*!
*   On va devoir coder run, header, print, mettre en place un fichier d'output,
*   faire une matrice de n colonnes et t lignes
*/
