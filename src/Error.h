#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <vector>

/*!
 * \class Error
   \brief This is a error handling class.
  
  Each error type has a specific exit code.
  Error messages will be passed by the exception caller.
  An Error can be thrown with a specific code and message.
 */
 
class Error : public std::runtime_error 
{
  public:
  /*! \name Constructors
 */
///@{
	/*!
   \param c (char): a character
   \param v (int): the code number, 0 by default
   */
    Error(const char *c, int v = 0) : std::runtime_error(c), code(v) {}
    /*!
   \param s (string): 
   \param v (int): the code number, 0 by default
   */
    Error(const std::string &s, int v = 0) : std::runtime_error(s), code(v) {}
    ///@}
    /*!
    It will return the code
    */
    int value() const {return code;}
     
    ///@{
    /*!
    It will set the error
    * \param msg (string): the message corresponding to an error
    * \param autoThrow (bool): it is true by default
    */
    static void set(const std::string& msg, bool autoThrow = true);
    /*!
    It will set the error
    * \param msg (string): the message corresponding to an error
    * \param v (int): the code number
    * \param autoThrow (bool): it is true by default
    */
    static void set(const std::string& msg, int v, bool autoThrow = true);
    ///@}

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
