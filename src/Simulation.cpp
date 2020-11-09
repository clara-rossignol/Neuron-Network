#include "constants.h"
#include "Simulation.h"
#include "Random.h"


Simulation::Simulation(int argc, char **argv) {
   try {
        TCLAP::CmdLine cmd(_PRGRM_TEXT_);
        TCLAP::ValueArg<int> total_n("N", "neurons", _NUMBER_TEXT_, false, _AVG_NUMBER_, "int");
        cmd.add(total_n);
        TCLAP::ValueArg<double> pE("p", "excitatory_neurons", _PROP_TEXT_, false, _AVG_PROP_, "double");
        //here I got an error: Argument flag can only be one character long Argument. That is why I changed pE to p.
        cmd.add(pE);
        TCLAP::ValueArg<int> maxt("t", "time", _TIME_TEXT_, false, _TIME_, "int");
        cmd.add(maxt);
        TCLAP::ValueArg<double> connectivity("c", "connectivity", _CNNCT_TEXT_, false, _AVG_CNNCT_, "double");
        //here i got the same error that is why I changed it to c.         
        cmd.add(connectivity);
        TCLAP::ValueArg<double> intensity("L", "intensity", _INTENSITY_TEXT_, false, _AVG_INTENSITY_, "double");
        cmd.add(intensity);
        
         TCLAP::ValueArg<std::string> ofile("o", "outptut", _OUTPUT_TEXT_, false, "", "string");
        cmd.add(ofile);
        
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
}catch(TCLAP::ArgException &e) {
        throw(TCLAP_ERROR("Error: " + e.error() + " " + e.argId()));
    }
}
 

void Simulation::run(){
	

}

void Simulation::print() {

}

Simulation::~Simulation() {

}

/*!
*   On va devoir coder run, header, print, mettre en place un fichier d'output,
*   faire une matrice de n colonnes et t lignes
*/
