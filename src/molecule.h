#ifndef HF_MOLECULE_H
#define HF_MOLECULE_H

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdio.h>

// Highest atomic number we need is 100
// Not the most general prescription - however, consider how large the need for
// ununoctium is in your biology

using namespace std;

#define FORMAT_SPECIFICATION "Syntax:\n\
Z:5\n\
100 22 33\n\
22 33 55\n\
Z:12\n\
3 4 -2\n\n\
(X Y Z) Positions in Angstrom"

// Wrapper for convenience
typedef struct {
    double vals[3];
} vector3_t;

class Molecule{
public:
    Molecule();
    Molecule(const string &filename);
    ~Molecule();
    void import_from(const string &filename);
    void print();
    uint nelectrons;
    void save_as(const string &filename);
private:
    void store_vector(uint Z, vector<vector3_t> v);
protected:
    double** nuclei;
    const static uint NELEM = 100;
    uint len[100];
};

#endif
