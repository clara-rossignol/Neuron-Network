#include "constants.h"
#include "Neuron.h"


const std::map<std::string, NeuronParams> Neuron::NeuronTypes{
    {"RS",  {.02, .2,  -65, 8,   false}},
    {"FS",  {.1,  .2,  -65, 2,   true }}
};

Neuron::Neuron()
:
{
 intializeValue(membrane_potential,recovery_variable);//not sure about this one
 setType("RS");
}
void Neuron::setParameters(const NeuronParams &params, double noise)
{
   if (params.inhib) 
      {
            params.a *= 1-0.8*noise;//maybe make them constants in constants.h
            params.b *= 1+0.25*noise;
        } else {
            noise *= noise;
            params.c *= 1-0.23*noise;
            params.d *= 1-0.75*noise;
        }	
};

void Neuron::initializeValue(double potential,double recovery)
{
	potential=65;//vinit=65 could be a constant in constants.h
	recovery=nparams.b*potential;
}
double Neuron::currentCalculation()
{
	
}
void Neuron::reset() 
{ membrane_potential=nparams.c; 
  recovery_variable+=nparams.d;
  
}
void Neuron::setType(std::string type){
	
}

bool Neuron::isFiring() const
{
	return (membrane_potential>30);//maybe firing_const could be a constant in .h
}
bool Neuron::isInhibitory() const
{
	return nparams.inhib;
}

