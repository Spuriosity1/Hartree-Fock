#ifndef ORBITAL_H
#define ORBITAL_H

#include <cmath>
#include <complex>
#include <stdio>
#include <assert.h> // compile with -DNDEBUG to remove assertions
#include "Eigen/Core"
#include "laguerrecoeff.h"

#ifndef NDEBUG
#warning Debug is enabled - this may hurt performance!
#endif


using namespace std;


double radial(uint n, uint l, double r);



#endif /* end of include guard: ORBITAL_H */
