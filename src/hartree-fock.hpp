#ifndef HARTREE_FOCK_CPP_H
#define HARTREE_FOCK_CPP_H

#include <Eigen/Eigenvalues>
// #include <nlohmann/json.hpp>
#include "molecule.hpp"
using namespace Eigen;

typedef struct {
    uint A; // nucleus number
    // quantum numbers
    unit n;
    uint l;
    int m;
} e_idx_t;

class HartreeFockSolver : public Molecule{
public:
    HartreeFockSolver() {};
    HartreeFockSolver(const std::vector<scalarfield_t> &phi);
};

#endif /* end of include guard: HARTREE_FOCK_CPP_H */
