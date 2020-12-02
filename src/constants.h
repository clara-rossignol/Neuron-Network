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
/*!
  A base class for errors thrown in this program.
  Each error type has a specific exit code.
  Error messages will be passed by the exception caller.
*/

/*class SimulError : public std::runtime_error 
{
public:
    SimulError(const char *c, int v=0) : std::runtime_error(c), code(v) {}
    SimulError(const std::string &s, int v=0) : std::runtime_error(s), code(v) {}
    int value() const {return code;}
protected:
    const int code;
};*/

#define _SIMULERR_(_N, _id) class _N : public Error { \
    public: _N(const char *c) : Error(c,_id) {} \
            _N(const std::string &s) : Error(s,_id) {} };


/// *Specific error codes*
_SIMULERR_(TCLAP_ERROR, 10)
_SIMULERR_(CFILE_ERROR, 20)
_SIMULERR_(OUTPUT_ERROR, 30)

#undef _SIMULERR_

/// * default parameter values *
#define _AVG_NUMBER_ 100
#define _AVG_PROP_ 0.2
#define _TIME_ 10
#define _AVG_CNNCT_ 40
#define _AVG_INTENSITY_ 4

#define _FIRING_TRESHOLD_ 30
#define _DELTA_MBRN_ 1
#define _DELTA_RECV_ 0.5


/// * parameter limits
#define _MIN_NEURONS_ 2
//#define _MAX_NEURONS_ 100000000 // should not be bigger than 2147483647

#define _MIN_TIME_ 0
#define _MAX_TIME_ 1000000000 // need verification

#define _MIN_PE_ 0.
#define _MAX_PE_ 1.

#define _MIN_CONNECTIVITY_ 0.
//#define _MAX_CONNECTIVITY_ _MAX_NEURONS_ - 1 // can i do that ?

#define _MIN_INTENSITY_ 0.
//#define _MAX_INTENSITY_ 100000. // To define


/// * error handling for TCLAP
/*!
* 0 : "The number of neurons should be between " << _MIN_NEURONS << "and " << _MAX_NEURONS << endl;
* 1 : "The number of steps should be between " << _MIN_TIME_ << "and " << _MAX_TIME_ << endl;
* 2 : "The proportion of excitatory neurons should be between 0 and 1" << endl;
* 3 : "The maximum number of connectivity should be between " << _MIN_CONNECTIVITY_ << "and " << _MAX_CONNECTIVITY_ << endl;
* 4 : "The intensity of a connection should be between " << _MIN_INTENSITY_ << "and " << _MAX_INTENSITY_ << endl;
*/

/// * text messages *
#define _PRGRM_TEXT_ "Simulation of the Izhikevich neuron model"
#define _NUMBER_TEXT_ "Number of neurons"
#define _PROP_TEXT_ "Proportion of inhibitor neurons"
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

struct NParams
{
    double a, b, c, d;
    bool inhib;
};

class Neuron;

struct Connection
{
    const Neuron* sender;
    const double intensity;
};

const std::map<std::string, NParams> NeuronTypes{
        {"RS",  {.02, .2,  -65, 8,   false}},
        {"IB",  {.02, .2,  -55, 4,   false}},
        {"CH",  {.02, .2,  -50, 2,   false}},
        {"FS",  {.1,  .2,  -65, 2,   true }},
        {"LTS", {.02, .25, -65, 2,   true }},
        {"TC",  {.02, .25, -65, .05, false}},
        {"RZ",  {.1,  .26, -65, 2,   false}},
};

typedef  std::map<std::string, double> TypesProportions;

#endif //GLOBALS_H
