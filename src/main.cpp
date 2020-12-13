#include "Random.h"
#include "Simulation.h"
#include <chrono>

/*!
  \mainpage Neuron Network
This is an implementation of the model of E.M. Izhikevich
([Simple Model of Spiking Neuron, IEE Trans. Neural Net., 2003] (https://www.izhikevich.org/publications/spikes.pdf)). \n
The model reproduces spiking and burting behaviour of known types of cortical neurons. \n
This project will simulate a neuron network.

  \authors  Lola Maïa Lou Bardel <lola.bardel@epfl.ch> \n
* 			Constance Laure Marie Géraldine Gabrielle De Trogoff Coatallio <constance.detrogoff@epfl.ch> \n
* 			Alexandra-Elena Preda <alexandra-elena.preda@epfl.ch> \n
* 			Clara Rossignol <clara.rossignol@epfl.ch>
 
In order to **open** the project, the user can clone the repository using this command:
 \verbatim 
  git clone https://gitlab.epfl.ch/sv_cpp_projects/team_12.git
 \endverbatim
 
To **execute** the program, the user has to write the following commands in the terminal:
 \verbatim
 cd team_12
 mkdir build
 cd build
 cmake ..
 make
 \endverbatim

After building, running and compiling the program, the user can type into the terminal a command like this typical example :
\verbatim
./NeuronNetwork -B -T 'FS:0.2,IB:0.15,CH:0.15,RS:0.5' -i 0.2 -t 1000 -N 10000 -c 40 -L 4 -l 2
\endverbatim

where **t** is the number of time-steps, **N** is the number of neurons, **T** the proportions of each type of neurons as a list
and **i** the proportion of inhibitory neurons. **c** is the average connectivity of a neuron, **L** is the average connections' intensity
and **C**, **O**, **B** represent the types of network the user can choose from, constant, overdispersed and basic, respectively.

Note that the parameters c, L and i are optional, as they are default parameters in our program. The default parameter for c is 1, for L it
is 4.
i is also an optional parameter but if its value is not precised in the command line, the program will run without using any value for i

Concerning the list of proportions, the user can add proportions for all existing types. If he doesn't specify the RS proportion,
the program will add RS neurons in order  to reach a total proportion of 1. In the same way, if the user doesn't specify the FS proportion
but did specify the total inhibitor's proportions, the program will add FS neurons in order to reach the total inhibitor's proportions.

In this manner, for a standard mode, the user can launch the program with only FS and RS types in four ways :
\verbatim
./NeuronNetwork -B -t 500 -N 1000 -T "RS:0.7,FS:0.3"
\endverbatim
or
\verbatim
./NeuronNetwork -B -t 500 -N 1000  -i 0.3 -T""
\endverbatim
or
\verbatim
./NeuronNetwork -B -t 500 -N 1000  -i 0.3 -T "RS:0.7"
\endverbatim
or
\verbatim
./NeuronNetwork -B -t 500 -N 1000 -T "FS:0.3"
\endverbatim

For a more complex network, the user can also launch the program with all types of neurons in four ways, but we only specify two as it would be redundant otherwise :
\verbatim
./NeuronNetwork  -B -t 500 -N 1000 -T "IB:0.2,FS:0.3, CH:0.1, LTS:0.1, RZ:0.1, RS: 0.2"
\endverbatim
or
\verbatim
./NeuronNetwork  -B -t 500 -N 100 -i 0.4 -T "IB:0.2, CH:0.1, LTS:0.1, RZ:0.1"
\endverbatim
*/


RandomNumbers *_RNG;

int main(int argc, char **argv) 
{
	auto t1 = std::chrono::high_resolution_clock::now();
    _RNG = new RandomNumbers();

    try {
		Simulation s(argc, argv);
		s.run();
	} catch(Error &e) {
        std::cerr << e.what() << std::endl;
        return e.value();
    }

    if (_RNG) delete _RNG;

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();

    std::cout << duration/1000. << " s" << std::endl ;
    std::cout << duration/(60. * 1000) << " min" << std::endl ;
    return 0;
}

