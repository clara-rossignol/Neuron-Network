#ifndef NEURON_H
#define NEURON_H

#include "constants.h"
/*!
  This is a neuron class.
*/

struct NeurParams {double a, b, c, d;
	              bool inhib;};

class Neuron {
static const std::map<std::string, NeurParams> NeuronTypes;

	Neuron(std::string);
public:
void setParameters(const NeurParams, double n=0.0);
void setType(std::string);
void initializeValue();
double currentCalculation();
bool isFiring() const;
bool isInhibitory() const;
void afterFiring();
private:

bool firing;
double membrane_potential;
double recovery_variable;
NeurParams nparams;



};
#endif //NEURON_H
