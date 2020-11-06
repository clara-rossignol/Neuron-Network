#include "constants.h"
#include "Simulation.h"
#include "Random.h"

Simulation::Simulation(int argc, char **argv) {
    try {
        TCLAP::CmdLine cmd(_PRGRM_TEXT_);
        TCLAP::ValueArg<int> total_n("N", "neurons", _NUMBER_TEXT_, false, _AVG_NUMBER_, "int");
        cmd.add(total_n);
        TCLAP::ValueArg<double> pE("pE", "excitatory neurons", _PROP_TEXT_, false, _AVG_PROP_, "double");
        cmd.add(pE);
        TCLAP::ValueArg<int> maxt("t", "time", _TIME_TEXT_, false, _END_TIME_, "int");
        cmd.add(maxt);
        TCLAP::ValueArg<double> connectivity("λ", "connectivity", _CNNCT_TEXT_, false, _AVG_CNNCT_, "double");
        cmd.add(connectivity);
        TCLAP::ValueArg<double> intensity("L", "intensity", _INTENSITY_TEXT_, false, _AVG_INTENTITY_, "double");
        cmd.add(intensity);
        //not sure if this is needed
        TCLAP::ValueArg<long> seed("S", "seed", "Random seed", false, 0, "long");
        cmd.add(seed);
        cmd.parse(argc, argv);
        //not sure if this is needed
        _RNG = new RandomNumbers(seed.getValue());
        
        _neurons = total_n.getValue();
        _pE = pE.getValue();
        _end_time = maxt.getValue();
        _connectivity = connectivity.getValue();
        _intensity = intensity.getValue();
}

Simulation::~Simulation() {
}
