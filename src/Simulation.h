//include
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
  * @param _time The duration of the simulation (in number of steps)
  * @param _connectivity The average connectivity
  * @param _intensity The average intensity of connections
*/
///@{
    Simulation(int, char**);
    ~Simulation();
///@}


private: 
    int _neurons;
    double _pE, _time, _connectivity, _intensity;
};
