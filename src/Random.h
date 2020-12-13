#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <vector>
#include <algorithm>

/*! \class RandomNumbers
 *  \brief This class generates random numbers.
 *  
 *  This is a random number class based on standard c++-11 generators.
 */

class RandomNumbers 
{
public:
/*! \name Initialization
 */
///@{
/*! The generator rng is a Mersenne twister *mt19937* engine. 
 *  A seed *s>0* can be provided, by default it is seeded with a *random_device*.
 */
///@{
    RandomNumbers(unsigned long int s=0);
///@}

/*! \name Distributions
 *  These functions return a single number.
 */
///@{
    double uniform_double(double lower, double upper);
    int uniform_int(double lower, double upper);
    double normal(double mean, double sd);
    int poisson(double mean);
    double exponential(double rate);
///@}

private:
    std::mt19937 _rng;
    long int _seed;
};

extern RandomNumbers *_RNG;

#endif //RANDOM_H
