#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <vector>
#include <algorithm>

/*!
  This is a random number class based on standard c++-11 generators.
*/

class RandomNumbers {

public:
/*! @name Initializing
  The generator \ref rng is a Mersenne twister *mt19937* engine. 
  A seed *s>0* can be provided, by default it is seeded with a *random_device*.
*/
///@{
    RandomNumbers(unsigned long int s=0);
///@}
/*! @name Distributions
  These functions return a single number.
*/
///@{
    double uniform_double(double lower, double upper);
    int uniform_int(double lower, double upper);
    double normal(double mean, double sd);
    int poisson(double mean);
///@}

private:
    std::mt19937 rng;
    long int seed;

};

extern RandomNumbers *_RNG;

#endif //RANDOM_H
