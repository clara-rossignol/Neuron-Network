#include "Random.h"

RandomNumbers::RandomNumbers(unsigned long int s) 
:_seed(s)
{
	if (_seed == 0) {
		std::random_device rd;
		_seed = rd();
	}
	_rng.seed(_seed);
}

double RandomNumbers::uniform_double(double lower, double upper) {
	std::uniform_real_distribution<> unif(lower, upper);
	return unif(_rng);
}

int RandomNumbers::uniform_int(double lower, double upper)
{
    std::uniform_int_distribution<> unif(lower, upper);
    return unif(_rng);
}

double RandomNumbers::normal(double mean, double sd)
{
	std::normal_distribution<> norm(mean, sd);
	return norm(_rng);
}

int RandomNumbers::poisson(double mean)
{
	std::poisson_distribution<> poiss(mean);
	return poiss(_rng);
}

double RandomNumbers::exponential(double rate) {
    std::exponential_distribution<double> exp(rate);
    return exp(_rng);
}
