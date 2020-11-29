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

  @authors  Alexandra-Elena Preda <alexandra-elena.preda@epfl.ch> <br>
* 			Clara Rossignol <clara.rossignol@epfl.ch> <br>
* 			Constance Laure Marie Géraldine Gabrielle De Trogoff Coatallio <constance.detrogoff@epfl.ch> <br>
* 			Lola Maïa Lou Bardel <lola.bardel@epfl.ch>

 The given command is: 
  \verbatim
  ./NeuronNetwork -T 'FS:0.2,IB:0.15,CH:0.15,RS:0.5' -t 500 -N 10000
  \endverbatim

*/

RandomNumbers *_RNG;

int main(int argc, char **argv) 
{    
  /*
  / This is for the programm to write the errors that happened 
  */
  std::atexit(&Error::write);
    _RNG = new RandomNumbers();

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
