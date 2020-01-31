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





void HartreeFockSolver::solve(){
    Eigen::GeneralizedSelfAdjointEigenSolver<MatrixXd> es;
    comp_S();
    while (Delta > max_toletance){
        comp_F();
    }

}
