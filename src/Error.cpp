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
    std::string m = std::string("Error ") + std::to_string(v) + std::string(": ") + msg;
    std::cout << m << std::endl;
    if (autoThrow) throw Error(m, v);
}
