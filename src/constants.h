#include <tclap/CmdLine.h>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

/*!
  A base class for errors thrown in this program.
  Each error type has a specific exit code.
  Error messages will be passed by the exception caller.
*/
class SimulError : public std::runtime_error {
public:
    SimulError(const char *c, int v=0) : std::runtime_error(c), code(v) {}
    SimulError(const std::string &s, int v=0) : std::runtime_error(s), code(v) {}
    int value() const {return code;}
protected:
    const int code;
};

#define _SIMULERR_(_N, _id) class _N : public SimulError { \
    public: _N(const char *c) : SimulError(c,_id) {} \
            _N(const std::string &s) : SimulError(s,_id) {} };


/// *Specific error codes*
_SIMULERR_(TCLAP_ERROR, 10)
_SIMULERR_(CFILE_ERROR, 20)
_SIMULERR_(OUTPUT_ERROR, 30)

#undef _SIMULERR_

/// * default parameter values *
#define _AVG_NUMBER_ 100
#define _AVG_PROP_ 0.8.
#define _TIME_ 10
#define _AVG_CNNCT_ 3 //am really not sure about this one, pretty much invented 
#define _AVG_INTENSITY_ 2 //same thing with this one

/// * text messages *
#define _PRGRM_TEXT_ "Simulation of the Izhikevich neuron model"
#define _NUMBER_TEXT_ "Number of neurons"
#define _PROP_TEXT_ "Proportion of excitatory neurons"
#define _TIME_TEXT_ "Number of time-steps"
#define _CNNCT_TEXT_ "Average connectivity"
#define _INTENSITY_TEXT_ "Average connections' intensity"
//useful ?
#define _OUTPUT_TEXT_ "Output file name (default is output to screen)"
#define _CFILE_TEXT_ "Configuration file name"
