#ifndef SIMULATION_H
#define SIMULATION_H

#include "Network.h"

/*! \class Simulation
    \brief The Simulation class is the main class in this program. 
    It constructs the Network according to user-specified parameters 
    and \ref run "runs" the Simulation. \n
        
    Simulation results are printed on three output files: \n
    * - **spikes**: the firing state of the neurons in the Network 
					in a matrix. \n
    * - **parameters**: the parameters of all the neurons in the Network 
						at the beginnig of the Simulation. \n
    * - **sample_neurons**: the membrane potential, recovery variable 
							and current of one Neuron of each type in 
							the Network throughout the Simulation. \n
    */   


class Simulation 
{
public:
/*! \name Initialization
 */
///@{
/*! Simulation takes the command-line options and extracts 
	the following parameters from them:
  * \param _size The total number of neurons in the network
  * \param _endtime The duration of the simulation (in number of steps)
  * \param _degree The average connectivity
  * \param _strength The average intensity of connections
  * \param _output The name of the output files 
		   (a suffix will be added depending on the file)
  * \param _thalamic The standard deviation of thalamic input 
		   (for excitatory neurons)
  * \param typesProp Proportions of each type of neuron as a list like 
		   "IB:0.2,FS:0.3,CH:0.2": By default all type proportions are 
		   set to 0 and if total is less than 1, it will be completed 
		   with RS neurons
  * \param networkModels Network model: basic, constant or overdispersed
 */
    Simulation(int, char**);

/*! Simple constructor of Simulation. Does not allow the choice between 
	different Networks model : only a basic Network will be created.
  * Does not take into account values in command-line.
 */
    Simulation(const TypesProportions& prop = {{"RS",0}, {"IB",0}, 
				{"CH",0},{"TC",0}, {"RZ",0}, {"FS",0},  {"LTS", 0}},
                int size = 0, int endtime = 0, double degree = 0, 
                double strength = 0, double thalamic = 1, 
                const std::string& output = "" );

/*! \name Destructor
 */                         
    ~Simulation();
///@}

    /*!
      Reads a string such as *IB:0.2,FS:0.3,CH:0.2* and saves each 
      proportion corresponding to each type in _props. \n
      Except RS (and FS if the inhibitor proportion is given) all 
      non-specified proportions will remain 0.
      If the the inhibitor proportion is too big compared to all 
      inhibitor types proportions, the proportion of FS will be raised 
      accordingly (if it was not specified in the command line) with a 
      first call of \ref checkMatchingProportions.
      If proportions don't match each other, the program will stop.
      After that, in the same way, if the sum of all proportions is 
      smaller than 1, some RS will be added accordingly (if it was not 
      specified in the command line) with a second call of 
      \ref checkMatchingProportions. If proportions don't match each other,
      the program will stop.

     * \param types A string such as *IB:0.2,FS:0.3,CH:0.2*
     * \param inhibSet Specifies if the inhibitory proportion was given
					   in the command line
     * \param inhib Inhibitor proportion will be used only if *inhibSet*
					is true
     */
     void readTypesProportions(const std::string& types, bool inhibSet, double inhib);

    /*!
    if *max_sum* is too big compared to all types proportions saved 
    between *beg* and *end*, the proportion of *def* will be raised 
    accordingly. If proportions don't match each other, the program will 
    stop.

    * \param beg first neuron type to consider
    * \param end last neuron type to consider
    * \param def the proportion that will be modified
    * \param setDef if *def* proportion was specified in the command line
    * \param maxSum the maximum value the sum of all proportions can reach
    */
    static void checkMatchingProportions(Iterator beg, Iterator end, const Iterator& def, bool setDef, double maxSum);

    /*! \name Running the simulation
     Runs the simulation through a loop with \ref _endtime steps. 
     Writes on the 3 different output files.
    */
///@{
    void run() {run(_endtime);}
    void run(double);

    /*! Writes the header in the output file *sample_neurons*.
     */
    void sampleHeader(std::ostream *_outstr);
///@}

    /*! \return Proportions of each type of neuron in the Simulation
     */
    const TypesProportions &getProp() const;


    /*!
     Checks if a parameter given in the command line is not in the valid range of value
        * \tparam N numeric type
        * \param message :specific message precising which parameter to consider
        * \param x the paramteter tested
        * \param min the minimum value the given parameter can reach
        * \param max the maximum value the given parameter can reach
        */
    template<typename N>
    static void checkInBound( const std::string& message, 
                              N x, N min = std::numeric_limits<N>::min(), 
                              N max = std::numeric_limits<N>::max())
    {
        if (x > max or x <min)
        {
            set("Invalid data entered. " + message + " should be between " + std::to_string(min) 
                    + " and " + std::to_string(max), PARAM_ERROR, true);
        }
    } 


private:
    TypesProportions _props;
    Network* _net;
    int _endtime;
    double _thalamic;
    std::string _output;

};

#endif // SIMULATION_H
