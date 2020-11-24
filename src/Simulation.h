#ifndef SIMULATION_H
#define SIMULATION_H

#include "Network.h"
#include <tclap/CmdLine.h>

/*!
  The Simulation class is the main class in this program. It constructs neuron network according to user-specified parameters, and @ref run "runs" the simulation.

  Simulation results are ?? //not sure how to explain this part, will write it later when better understood

*/
typedef  std::map<std::string, double>::iterator Iterator ;

class Simulation 
{
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
    /*Simulation(const int _s, const int _t)
        :  _size(_s),_endtime(_t){}*/ //whhy is this needed ?
    Simulation(int, char**);

/*!
* Runs the simulation through a loop with \ref endtime steps.
*/

    void run() {run(_endtime);}
    void run(const double);

/*!
* Write on the output document at every steps, called in ru 
*/
    void print();
    void header();

    ~Simulation();
///@}

private: 

  Network _net;
  int _size;
  int _endtime;
  double _degree, _strength;
  std::string outfile;

    static void checkTypes(Iterator beg, Iterator end, const Iterator& def, double max_sum);

    template<typename N>
    void checkInBound( const std::string& message, N x, N min = std::numeric_limits<N>::min(), N max = std::numeric_limits<N>::max())
    {
        if (x > max or x <min)
        {
            Error::set("Invalid data entered", 1);
            std::cerr << message <<" should be between " << min << "and " << max << std::endl;
        }
    }

    TypesProportions readTypesProportions(std::string types, bool inhibSet, double inhib);
};

#endif // SIMULATION_H
