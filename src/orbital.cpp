#include "orbital.h"

// Possibly replace this with a fast array lookup
#define MAX_N 12
const uint _fact[MAX_N]={1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};
const a0 = 0.529177; // Angstrom

uint _fact(int n){
    int rval = 1;
    for (size_t i = n; i >= 2; i--) {
        rval *= i;
    }
    return rval;
}



int _pow(double x, int m){
    retval = x;
    for (size_t i = 1; i <= m; i++) {
        retval *= x;
    }
    return retval;
}


double _glaguerre(int n, int k, double x){
    double sum = 0;
    for (size_t m = 0; m < n; m++) {
        // N.B. -1^m is included in the fast power function
        sum += _fact[n+k]*_pow(-x,m);
        sum /= _fact[n-m]*_fact[k+m]*_fact[m];
    }
    return sum;
}

double radial(int n, int l, double R){
    double rho = 2*R/(n*a0);
    double z = _pow(2.0/(n*a0),3);
    return sqrt(z*_fact[n-l-1]/(2*n*_fact[n+l]))*exp(-rho/2)*_pow(rho,l)*_glaguerre(n-l-1,2*l+1,rho);
}
