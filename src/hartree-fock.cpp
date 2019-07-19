#include "hartree-fock.hpp"

/*
What it says on the tin

Iteratively solves the generalised evalue problem
Using a basis \phi_n:

F(C[n]) C[n+1] = S C[n+1] E
where
S_{\mu\nu} = \int dx \phi^*_{mu}(x)\phi_\nu(x)
F_{\mu\nu} = \int dx \phi^*_{mu}(x) f(x) \phi_\nu(x)

f(x) is the Fock operator, f(x) = h(x) + \sum_j J_j(x) - K_j(x)
N.B. K is an operator, not a number in the above expression!

*/





// HartreeFockSolver::HartreeFockSolver (const std::vector<scalarfield_t> &phi){
//
// }


// void HartreeFockSolver::solve(const MatrixXd&phi , const Ref<const ArrayXXd> U){
//     Eigen::GeneralizedSelfAdjointEigenSolver<MatrixXd> es;
// }
