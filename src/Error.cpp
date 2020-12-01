#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Error.h"

std::vector<std::string> Error::err;


std::string Error::last()
{
    return (err.size() == 0) ? std::string("") : err[err.size() - 1];
}

void Error::write()
{
    std::ofstream file;
    file.open("error.txt", std::ofstream::out | std::ofstream::trunc);
    file << std::string("Errors count: ") + std::to_string(count()) << std::endl << std::endl;
    for (size_t i(0); i < err.size(); ++i)
    {
        file << err[i] << std::endl;
    }
}

void Error::set(std::string const& msg, bool autoThrow)
{
    set(msg, 0, autoThrow);
}

void Error::set(std::string const& msg, int v, bool autoThrow)
{
    std::string m = std::to_string(v) + std::string(": ") + msg;
    std::cout << m << std::endl;
    err.push_back(m);

    if (autoThrow)
    {
        throw Error(m, v);
    }
}

size_t Error::count()
{
    return err.size();
}