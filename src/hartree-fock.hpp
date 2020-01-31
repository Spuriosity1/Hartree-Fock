#ifndef HARTREE_FOCK_CPP_H
#define HARTREE_FOCK_CPP_H

#include <Eigen/Eigenvalues>
// #include <nlohmann/json.hpp>
#include "molecule.hpp"
using namespace Eigen;

class HartreeFockSolver : public Molecule{
public:
    HartreeFockSolver() {};
    void solve();
};

#endif /* end of include guard: HARTREE_FOCK_CPP_H */
