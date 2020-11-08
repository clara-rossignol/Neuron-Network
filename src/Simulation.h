#include "Network.h"
#include <tclap/CmdLine.h>

/*!
  The Simulation class is the main class in this program. It constructs neuron network according to user-specified parameters, and @ref run "runs" the simulation.

  Simulation results are ?? //not sure how to explain this part, will write it later when better understood

*/

class Simulation {
public:
/*! @name Initialization
  Simulation takes the command-line options and extracts the following parameters from them:
  * @param _size The total number of neurons in the network
  * @param _pE The proportion of excitatory neurons
  * @param _endtime The duration of the simulation (in number of steps)
  * @param _connectivity The average connectivity
  * @param _intensity The average intensity of connections
*/
///@{
/*!
 * Constructor based on user inputs, takes command-line arguments.
 */ 
    Simulation(int, char**);
    
/*!
 * Runs the simulation through a loop with \ref endtime steps.
*/
    void run();
    
    ~Simulation();
///@}


private: 
    Network _net; 
    size_t _size;
    int _endtime;
    double _pE, _connectivity, _intensity;
    //other to add ?
};
