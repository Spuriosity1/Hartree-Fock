#include <iostream>
#include <string>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "molecule.h"
#include "Eigen/Eigenvalues"

class HFsolver {
public:
    Molecule molecule;
    void solve();
}

// CALL SEQUENCE
// HFsolve input_file.dat
// input_file has the 3D coordinates of all atoms, with some syntax specified
// in moleculeio.h
int main(int argc, char const *argv[]) {
    if (argc < 2){
        cerr << "Please specify an input file." <<endl;
        cerr << FORMAT_SPECIFICATION <<endl;
        exit(EXIT_FAILURE);
    }
    string path(argv[1]);
    Molecule M(path);
    M.print();

    return 0;
}