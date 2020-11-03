#include "Network.h"

/*!
  The Simulation class is the main class in this program. It constructs neuron network according to user-specified parameters, and @ref run "runs" the simulation.

  Simulation results are ?? //not sure how to explain this part, will write it later when better understood

*/

class Simulation {
public:
/*! @name Initialization
  Simulation takes the command-line options and extracts the following parameters from them:
  * @param _neurons The total number of neurons in the network
  * @param _pE The proportion of excitatory neurons
  * @param _end_time The duration of the simulation (in number of steps)
  * @param _connectivity The average connectivity
  * @param _intensity The average intensity of connections
*/
///@{
    Simulation(int, char**);
    ~Simulation();
///@}


private: 
    Network _net; //might not be the right class name
    size_t _neurons;
    int _end_time;
    double _pE, _connectivity, _intensity;
    //other to add ?
};
