#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <vector>
/*!
 * \class Error
   \brief This is a class that deals with the errors
  
  Each error type has a specific exit code.
  Error messages will be passed by the exception caller.
  Error with specific code and message can be thrown
   
 */
class Error : public std::runtime_error 
{
  public:
    Error(const char *c, int v = 0) : std::runtime_error(c), code(v) {}
    Error(const std::string &s, int v = 0) : std::runtime_error(s), code(v) {}
    int value() const {return code;}

    static void set(const std::string& msg, bool autoThrow = true);
    static void set(const std::string& msg, int v, bool autoThrow = true);

  protected:
    const int code;
};

#define _ERROR_(_N, _id) class _N : public Error \
{\
  public : \
    _N(const char *c) : Error (c,_id) {} \
    _N(const std::string &s) : Error(s,_id) {} \
};


/// *Specific error codes*
_ERROR_(TCLAP_ERROR, 10)
_ERROR_(CFILE_ERROR, 20)
_ERROR_(OUTPUT_ERROR, 30)


#undef _ERROR_

#endif // ERROR_H