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
      Read a string such as *IB:0.2,FS:0.3,CH:0.2* and saves each proportion corresponding to each type.
      By default, all proportions are set to 0.
      Except RS (and FS if the inhibitor proportion is given) all non-specified proportions will remain 0.
      If the the inhibitor proportion is too big compared to all inhibitor types proportions,
      the proportion of FS will be raised accordingly (if it was not specified in the command line)
      with a first call of /ref checkTypes. If proportions don't match each other, the program will stop
      After that, in the same way, if the sum of all proportions is smaller than 1,
      some RS will be added accordingly (if it was not specified in the command line).
      with a second call of /ref checkTypes. If proportions don't match each other, the program will stop

     * @param types : a string such as *IB:0.2,FS:0.3,CH:0.2*
     * @param inhibSet specify if the inhibitory proportion was given in the command line
     * @param inhib inhibitor proportion will be used only if *inhibSet* is true
     * @return the recording of all type proportions
     */
    TypesProportions readTypesProportions(std::string types, bool inhibSet, double inhib);

    /*!
      if *max_sum* is too big compared to all types proportions saved between *beg* and *end*, the proportion of *def*
      will be raised accordingly. If proportions don't match each other, the program will stop

     * @param beg first neuron type to consider
     * @param end last neuron type to consider
     * @param def the proportion that will be modified
     * @param setDef if *def* proportion was specified in the command line
     * @param max_sum the maximum value the sum of all proportions can reach
     */
    static void checkTypes(Iterator beg, Iterator end, const Iterator& def, bool setDef,  double max_sum);

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
 /*!
     *
     * @tparam N
     * @param message
     * @param x
     * @param min
     * @param max
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


};

#endif // SIMULATION_H
