#include "constants.h"
#include "Random.h"
#include "Simulation.h"

//to be modified/completed
RandomNumbers *_RNG;

int main(int argc, char **argv) {    
    try {
        Simulation s(argc, argv);
        s.run();
    } catch(SimulError &e) {
        std::cerr << e.what() << std::endl;
        return e.value();
    }
    if (_RNG) delete _RNG;
    return 0;
}
