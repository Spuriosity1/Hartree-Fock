#ifndef MOLECULE_CPP_H
#define MOLECULE_CPP_H

#define GTO_EXPANSION_ORDER 10

// This class contains all of the electronic information involved in the molecular solution
// We will employ the predetermined sets of Gaussian-type orbitals for computational efficiency.

#include <Eigen/Dense>
#include "nuclei.hpp"

// R(r) = sum_s=0^M d_s exp(-alpha_s r^2)$$
typedef struct{
    double d[GTO_EXPANSION_ORDER];
    double a[GTO_EXPANSION_ORDER];
} GTO_t;

class Molecule : public Nuclei {
public:
    void construct_GTO();
    void comp_S();
    void comp_F();
private:
    void h(GTO_t &k1, GTO_t &k2);
    void J(GTO_t &k1, GTO_t &k2);
    void K(GTO_t &k1, GTO_t &k2);

    void zero_matrices();

    Eigen::MatrixXd F;
    Eigen::MatrixXd S;
    Eigen::MatrixXd C;

    std::vector<GTO_t> GTO;

};

#endif /* end of include guard: MOLECULE_CPP_H */
