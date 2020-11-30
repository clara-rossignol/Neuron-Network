#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <vector>
/*!
 * \class Error
   \brief This is a class that deals with the errors
  
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

#endif
