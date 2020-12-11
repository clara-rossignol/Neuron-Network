#ifndef SIMULATION_H
#define SIMULATION_H

#include "Network.h"
#include <tclap/CmdLine.h>

/*! \class Simulation
    \brief The Simulation class is the main class in this program. 
    
    It constructs the \ref Network \ref _net according to user-specified parameters, and \ref run "runs" the \ref Simulation. \n
    * Simulation results are three output files: \n
    * - **spikes** : the firing state of the neurons in the \ref Network in a matrix \n
    * - **parameters** : the parameters of all the neurons in the \ref Network at the end of the \ref Simulation \n
    * - **sample_neurons** : the membrane potential, recovery variable and current of one \ref Neuron of each type in the \ref Network throughout the \ref Simulation \n
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

/*! \name Constructor
 */
///@{
	/*!Constructor based on user inputs, takes command-line arguments.
	 */ 
    Simulation(int, char**);

    // permet uniquement de créer un network basique
    Simulation(const TypesProportions& prop = {{"RS",0}, {"IB",0}, {"CH",0},{"TC",0}, {"RZ",0}, {"FS",0},  {"LTS", 0}},
               int size = 0, int endtime = 0, double degree = 0, double strength = 0, double thalamic = 1, const std::string& output = "" );

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

    /*!
* Runs the simulation through a loop with \ref _endtime steps. Writes on the 3 different output files.
*/
    void run() {run(_endtime);}
    void run(double);
    
    /*! Writes the header in the output file *sample_neurons*.
     */
    void sample_header(std::ostream *_outstr);

    const TypesProportions &getProp() const;

/*! \name Destructor
 */
///@{
    ~Simulation();
///@}

private: 
	/*! \name Network
	 */
    Network* _net;
    int _endtime;
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
        }
    }

};

#endif // SIMULATION_H
