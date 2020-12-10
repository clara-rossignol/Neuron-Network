#include "constants.h"
#include "Random.h"
#include "Simulation.h"
#include <chrono>

/*!
  \mainpage Neuron Network
This is an implementation of the model of E.M. Izhikevich
([Simple Model of Spiking Neuron, IEE Trans. Neural Net., 2003] (https://www.izhikevich.org/publications/spikes.pdf)).

  @authors  Alexandra-Elena Preda <alexandra-elena.preda@epfl.ch> \n
* 			Clara Rossignol <clara.rossignol@epfl.ch> \n
* 			Constance Laure Marie Géraldine Gabrielle De Trogoff Coatallio <constance.detrogoff@epfl.ch> \n
* 			Lola Maïa Lou Bardel <lola.bardel@epfl.ch>
 
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
 
 After building, running and compiling the program. the user can type into the terminal the following **commands**, depending on the mode he wants to use:
 For the standard mode (i.e. the network will only contain RS and LS neurons), the command is:
 \verbatim 
 ./NeuronNetwork -B -t 500 -N 10000 -T "FS:0.2,RS:0.8" -c 20
 \endverbatim
 
 For a more complex network,containing also the other types of neurons (IB,CH,LTS) write the following command:
 \verbatim
 ./NeuronNetwork -B -T 'FS:0.2,IB:0.15,CH:0.15,RS:0.5' -t 1000 -N 10000 -c 40 -L 4
 \endverbatim
  
,where **t** is the number of time-steps, **N** is the number of neurons, **T** the proportions of each type of neurons as a list.
(If total is less than 1, it will be completed with RS neurons),**c** is the average connectivity of a neuron, **L** is the average connections' intensity and **i** the proportion of inhibitor neurons
and **C**, **O**, **B** represent the types of network the user can choose from, constant, overdispersed and basic, respectively.

Note that the parameters c, L and i are optional, as there are default parameters in our program
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
