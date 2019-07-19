#ifndef MOLECULE_CPP_H
#define MOLECULE_CPP_H

#define GTO_EXPANSION_ORDER 10

// This class contains all of the electronic information involved in the molecular solution
// We will employ the predetermined sets of Gaussian-type orbitals for computational efficiency.

#include <Eigen/Dense>
#include "nuclei.hpp"

#define SQRT_PI 1.7724538509055159

using namespace Eigen;

// R(r) = sum_s=0^M d_s exp(-alpha_s r^2)$$
typedef struct{
    double d;
    double a;
    double n[3];
} GTO_term_t;

typedef struct{
    GTO_term_t terms[GTO_EXPANSION_ORDER];
} GTO_t;

class Molecule : public Nuclei {
public:
    Molecule(uint n);
    void construct_GTO();
    void comp_S();
    void comp_F();
private:
    void T();
    void Uen();
    void J();
    void K();

    void zero_matrices();

    uint N; // number of expansion coefficients, size of basis

    MatrixXd F;
    MatrixXd S;
    MatrixXd C;

    std::vector<GTO_t*> GTO; // N long

};

#endif /* end of include guard: MOLECULE_CPP_H */
