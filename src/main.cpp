#include "constants.h"
#include "Random.h"
#include "Simulation.h"
#include "Neuron.h"
#include "Network.h"
#include <tclap/CmdLine.h>

/*!
  \mainpage Neuron Network
This is an implementation of the model of E.M. Izhikevich
([Simple Model of Spiking Neuron, IEE Trans. Neural Net., 2003] (https://www.izhikevich.org/publications/spikes.pdf)).

 The given command is 
  \verbatim
  ./NeuronNetwork -t 500 -N 10000 -T ’IB:0.2,FS:0.3,CH:0.2’
  \endverbatim
  

*/
//to be modified/completed
RandomNumbers *_RNG;

int main(int argc, char **argv) 
{    
  /*
  / This is for the programm to write the errors that happened 
  */
  std::atexit(&Error::write);
    try {
        Simulation s(argc, argv);
       s.run();
    } catch(Error &e) {
        std::cerr << e.what() << std::endl;
        return e.value();
    }

    if (_RNG) delete _RNG;
    return 0;
}
