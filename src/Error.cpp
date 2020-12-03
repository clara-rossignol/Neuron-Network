#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Error.h"

void Error::set(std::string const& msg, bool autoThrow)
{
    set(msg, 0, autoThrow);
}

void Error::set(std::string const& msg, int v, bool autoThrow)
{
    std::string m = std::to_string(v) + std::string(": ") + msg;
    std::cout << m << std::endl;

    if (autoThrow)
    {
        throw Error(m, v);
    }
}

/*
// #define _SIMULERR_(_N, _id) class _N : public Error 
{ \
    public: _N(const char *c) : Error(c,_id) {} \
            _N(const std::string &s) : Error(s,_id) {} };


/// *Specific error codes*
_ERR0R_(TCLAP_ERROR, 10)
_ERROR_(CFILE_ERROR, 20)
_ERROR_(OUTPUT_ERROR, 30)

#undef _SIMULERR_

*/