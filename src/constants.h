#ifndef GLOBALS_H
#define GLOBALS_H

#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

#include "Error.h"

/// * default parameters values *
#define _AVG_NUMBER_ 100
#define _AVG_PROP_ 0.2
#define _AVG_OUT_ "NeuronNetwork"
#define _AVG_THAL_ (_RNG->normal(0,1))
#define _TIME_ 10
#define _AVG_CNNCT_ 1.
#define _AVG_INTENSITY_ 4
#define _FIRING_TRESHOLD_ 30
#define _DELTA_MBRN_ 1.
#define _DELTA_RECV_ 0.5


/// * parameter limits *
#define _MIN_NEURONS_ 2
#define _MIN_TIME_ 0
#define _MIN_PE_ 0.
#define _MAX_PE_ 1.
#define _MIN_THALAM_ (-1/(sqrt(2*M_PI)))
#define _MAX_THALAM_ (1/(sqrt(2*M_PI)))
#define _MIN_CONNECTIVITY_ 0.
#define _MIN_INTENSITY_ 0.


/// * text messages *
#define _PRGRM_TEXT_ "Simulation of the Izhikevich neuron model"
#define _NUMBER_TEXT_ "Number of neurons"
#define _PROP_TEXT_ "Proportion of inhibitor neurons"
#define _OUT_TEXT_ "Output files name (suffix will be added)"
#define _THALAM_TEXT_ "Standard deviation of thalamic input (for excitatory neurons)"
#define _TIME_TEXT_ "Number of time-steps"
#define _CNNCT_TEXT_ "Average connectivity of a neuron"
#define _INTENSITY_TEXT_ "Average connections' intensity"
#define _TYPES_TEXT_ "Proportions of each type of neurons as a list like 'IB:0.2,FS:0.3,CH:0.2'. If total is less than 1, it will be completed with RS neurons"
#define _BASIC_TEXT_ "Basic model of connections"
#define _CONSTANT_TEXT "Constant model of connections"
#define _OVERDISPERSED_TEXT "Overdispersed model of connections"
#define _OUTFILE_1_ "spikes"
#define _OUTFILE_2_ "parameters"
#define _OUTFILE_3_ "sample_neurons"



/*! \brief This is how a Neuron's parameters are implemented.
 * The neuron parameters. *
 */
struct NParams
{
    double a, b, c, d;
    bool inhib;
};

class Neuron;

/*! \brief This is how a Neuron's connections are implemented. 
 * Connections are implemented as the neuron connected and the intensity of its connection.
 */
struct Connection
{
    const Neuron* sender;
    const double intensity;
};

/*! All the different neuron types and their parameters.
 */
const std::map<std::string, NParams> NeuronTypes{
        {"RS",  {.02, .2,  -65, 8,   false}},
        {"IB",  {.02, .2,  -55, 4,   false}},
        {"CH",  {.02, .2,  -50, 2,   false}},
        {"FS",  {.1,  .2,  -65, 2,   true }},
        {"LTS", {.02, .25, -65, 2,   true }},
        {"TC",  {.02, .25, -65, .05, false}},
        {"RZ",  {.1,  .26, -65, 2,   false}},
};

/*! \typedef The different types and their proportions in the \ref Network.
 */
typedef  std::map<std::string, double> TypesProportions;

#endif //GLOBALS_H
