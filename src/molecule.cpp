#include "molecule.hpp"

Molecule::Molecule(uint n){
    N=n;
    GTO.resize(n);
}


// template recursion -- this looks a little cursed to be honest
template <unsigned int exponent>
inline double intpow(double base) {
    return intpow<exponent-1>(base) * base;
}

template <>
inline double intpow<0>(double base) {
    return 1;
}

void Molecule::construct_GTO(){
}

void Molecule::comp_S(){}
void Molecule::comp_F(){}


// // small brain
// inline double i_fact(uint n){
//     double retval = 1;
//     for (size_t i = n; i >1; i--) {
//         retval *= i;
//     }
//     return retval;
// }
//
// // big brain
// inline double r_fact(uint n){
//     if (n <= 2){
//         return n;
//     } else {
//         return n*r_fact(n-1);
//     }
// }

// galaxy brain
const static double a_fact[20] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320,
    362880, 3628800, 39916800, 479001600, 6227020800, 87178291200,
    1307674368000, 20922789888000, 355687428096000, 6402373705728000,
    121645100408832000};

// returns integral of x^(n) exp(-ax^2)
inline double _gint(uint n, double a){
    if (n%2 ==1) return 0;
    n /= 2;
    return pow(a,-n-0.5)*a_fact[2*n]*SQRT_PI/(intpow(4,n) * a_fact[n]);
}


double x = 0;
GTO_t xp;
for (size_t s = 0; s < GTO_EXPANSION_ORDER; s++) {
    GTO_term_t term = xp[s];
    x += 2*term.a[s]*term.d[s]*(2*term.a[s]*x);
}

// Kinetic energy term, -1/2 nabla^2
void Molecule::T(){
    for (size_t mu = 0; mu < N; mu++) {
        for (size_t nu = 0; nu < N; nu++) {
            // <chi_mu | -0.5del^2 | chi_nu >
            F(mu, nu) -=1;

            GTO_t B1 = GTO[mu];
            GTO_t B2 = GTO[nu];

        }
    }
}

// Potential energy from e-N interactions
void Molecule::Uen(){

}

void Molecule::J(GTO_t &k1, GTO_t &k2){

}

void Molecule::K(GTO_t &k1, GTO_t &k2){

}

void Molecule::zero_matrices(){
    F = MatrixXd::Zero(N,N);
    S = MatrixXd::Zero(N,N);
    C = MatrixXd::Zero(N,nelectrons);
}

void Molecule::comp_S(){
    for (size_t mu = 0; mu < N; mu++) {
        for (size_t nu = 0; nu < N; nu++) {
            // <chi_mu | chi_nu >
            S(mu, nu) -= 1;

            GTO_t B1 = GTO[mu];
            GTO_t B2 = GTO[nu];
            
            for (size_t s = 0; s < GTO_EXPANSION_ORDER; s++) {
                for (size_t t = 0; t < GTO_EXPANSION_ORDER; t++) {
                    /* code */
                }
            }


        }
    }
}
