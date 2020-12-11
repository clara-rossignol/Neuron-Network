#ifndef SIMULATION_H
#define SIMULATION_H

#include "Network.h"

/*! \class Simulation
    \brief The Simulation class is the main class in this program. 
    It constructs the Network according to user-specified parameters and \ref run "runs" the Simulation. \n
        
    Simulation results are printed on three output files: \n
    * - **spikes**: the firing state of the neurons in the Network in a matrix. \n
    * - **parameters**: the parameters of all the neurons in the Network at the beginnig of the Simulation. \n
    * - **sample_neurons**: the membrane potential, recovery variable and current of one Neuron of each type in the Network throughout the Simulation. \n
    */   

/*! \typedef Iterator : to iterate through a map
 */
typedef  std::map<std::string, double>::iterator Iterator ;

class Simulation 
{
public:
/*! \name Initialization
  Simulation takes the command-line options and extracts the following parameters from them:
  * \param _size The total number of neurons in the network
  * \param _endtime The duration of the simulation (in number of steps)
  * \param _degree The average connectivity
  * \param _strength The average intensity of connections
  * \param _output The name of the output files (a suffix will be added depending on the file)
*/
///@{
    Simulation(int, char**);
///@}

    /*!
      Read a string such as *IB:0.2,FS:0.3,CH:0.2* and saves each proportion corresponding to each type. \n
      By default, all proportions are set to 0. \n
      Except RS (and FS if the inhibitor proportion is given) all non-specified proportions will remain 0.
      If the the inhibitor proportion is too big compared to all inhibitor types proportions,
      the proportion of FS will be raised accordingly (if it was not specified in the command line)
      with a first call of /ref checkTypes. If proportions don't match each other, the program will stop
      After that, in the same way, if the sum of all proportions is smaller than 1,
      some RS will be added accordingly (if it was not specified in the command line).
      with a second call of /ref checkTypes. If proportions don't match each other, the program will stop

     * \param types A string such as *IB:0.2,FS:0.3,CH:0.2*
     * \param inhibSet Specifies if the inhibitory proportion was given in the command line
     * \param inhib Inhibitor proportion will be used only if *inhibSet* is true
     * \return The recording of all type proportions
     */
     void readTypesProportions(const std::string& types, bool inhibSet, double inhib);

    /*!
      if *max_sum* is too big compared to all types proportions saved between *beg* and *end*, the proportion of *def*
      will be raised accordingly. If proportions don't match each other, the program will stop

     * \param beg first neuron type to consider
     * \param end last neuron type to consider
     * \param def the proportion that will be modified
     * \param setDef if *def* proportion was specified in the command line
     * \param max_sum the maximum value the sum of all proportions can reach
     */
    static void checkTypes(Iterator beg, Iterator end, const Iterator& def, bool setDef,  double max_sum);

    /*! \name Running the simulation
     Runs the simulation through a loop with \ref _endtime steps. Writes on the 3 different output files.
    */
///@{
    void run() {run(_endtime);}
    void run(const double);
    
    /*! Writes the header in the output file *sample_neurons*.
     */
    void sample_header(std::ostream *_outstr);
///@}

/*! \name Destructor
 */
///@{
    ~Simulation();
///@}

private: 
	/*! \name Network
	 */
 Network* _net;
  int _size;
  int _endtime;
  double _degree, _strength;
  double _thalamic;
  std::string _output;
  TypesProportions prop;
 /*!
     *
     * @tparam N
     * @param message
     * @param x
     * @param min
     * @param max
     */
    template<typename N>
    static void checkInBound( const std::string& message, N x, N min = std::numeric_limits<N>::min(), N max = std::numeric_limits<N>::max())
    {
        if (x > max or x <min)
        {
            Error::set(std::string("Invalid data entered. ") + message + std::string(" should be between ") 
                                    + std::to_string(min) + std::string(" and ") + std::to_string(max), 1);
            /*
            Error::set(" Invalid data entered", 1);
            std::cerr << message <<" should be between " << min << "and " << max << std::endl;
            */
        }
    }

};

#endif // SIMULATION_H
