#include "orbital.h"

const static double a0 = 0.529177; // Angstrom

const static double I = complex<float>(0,1);

const static complex<double> I(0,1);

int _pow(double x, int m){
    int retval = x;
    for (size_t i = 1; i <= m; i++) {
        retval *= x;
    }
    return retval;
}

double assoc_laguerre(uint n, uint k, double x){
    double sum =0;
    for (uint i = 0; i < n; i++) {
        sum += COEFF[n][l][a][k]*;
    }
    return sum;
}

complex<double> spherical(uint l, int m, double x, double y){
    return 0;
}

double radial(uint n, uint l, double r){
    assert(n-l-1>=0);
    double rho = 2*r/(n*a0);
    double z = _pow(2.0/(n*a0),3);
    return sqrt(z*_fact[n-l-1]/(2*n*_fact[n+l]))*exp(-rho/2)*_pow(rho,l)*laguerre(n-l-1,2*l+1,rho);
}

double radial(uint n, uint l, double r){
    assert(n-l-1>=0);
    double rho = 2*r/(n*a0);
    double z = _pow(2.0/(n*a0),3);
    return sqrt(z*_fact[n-l-1]/(2*n*_fact[n+l]))*exp(-rho/2)*_pow(rho,l)*laguerre(n-l-1,2*l+1,rho);
}

// complex<double> spherical(uint l, int m, double theta, double phi){
//     uint M = (uint) abs(m);
//     double z = (2*l + 1)*_fact[l-M]/(4*M_PI*_fact[l+M]);
//     if (m >= 0){
//         return altval(m)*sqrt(z)*assoc_legendre(l,M,cos(theta))*exp(I*m*theta);
//     } else {
//         return sqrt(z)*assoc_legendre(l,M,cos(theta))*exp(I*m*theta);
//     }
//
// }

// double assoc_laguerre(uint n, uint k, double x){
//     double sum = 0;
//     for (size_t m = 0; m < n; m++) {
//         // N.B. -1^m is included in the fast power function
//         sum += _fact[n+k]*_pow(-x,m);
//         sum /= _fact[n-m]*_fact[k+m]*_fact[m];
//     }
//     return sum;
// }
