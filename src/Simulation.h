#ifndef SIMULATION_H
#define SIMULATION_H

#include "Network.h"
#include <tclap/CmdLine.h>

/*! \class Simulation
    \brief The Simulation class is the main class in this program. 
    
    It constructs the \ref NeuronNetwork net \n  according to user-specified parameters, and @ref run "runs" the simulation.
    Simulation results are three  output files that //not sure how to explain this part, will write it later when better understood
    
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
  * @param _degree The average connectivity
  * @param _intensity The average intensity of connections
  * @param _strength: average intensity of connections
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
* Write on the output document at every steps, called in run 
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
  /*!
  Constraint function for a TCLAP argument to restrict a double to [0,1].
  */
  template<typename N>
  void checkInBound( const std::string& message, N x, N min = std::numeric_limits<N>::min(), N max = std::numeric_limits<N>::max())
  {
     if (x > max or x <min)
       {
            Error::set("Invalid data entered", 1);
            std::cerr << message <<" should be between " << min << "and " << max << std::endl;
        }
    }
  /*!
   Read the proportions for different types of neurons. The neuron types are found in \ref Neuron::NeuronTypes.
  */
  TypesProportions readTypesProportions(std::string types, bool inhibSet, double inhib);
};

#endif // SIMULATION_H
