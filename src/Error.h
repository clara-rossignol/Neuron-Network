#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <vector>

class Error : public std::runtime_error 
{
    public:
    Error(const char *c, int v = 0) : std::runtime_error(c), code(v) {}
    Error(const std::string &s, int v = 0) : std::runtime_error(s), code(v) {}
    int value() const {return code;}

    static void set(const std::string& msg, bool autoThrow = true);
    static void set(const std::string& msg, int v, bool autoThrow = true);
    static std::string last();
    static void write();
    static size_t count();

    protected:
    const int code;

    private:
    static std::vector<std::string> err;
};


#endif