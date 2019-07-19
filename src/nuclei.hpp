#ifndef HF_NUCLEI_H
#define HF_NUCLEI_H

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdio.h>

// Highest atomic number we need is 100
// Not the most general prescription - however, consider how large the need for
// ununoctium is in your biology

#define FORMAT_SPECIFICATION "Syntax:\n\
Z:5\n\
100 22 33\n\
22 33 55\n\
Z:12\n\
3 4 -2\n\n\
(X Y Z) Positions in Angstrom"

// Wrapper for convenience
typedef struct {
    double v[3];
} vector3_t;

class Nuclei{
public:
    Nuclei() {};
    Nuclei(const std::string &path);
    void import_from(const std::string &path);
    void print_nuclei();
    uint nelectrons;
    void save_as(const std::string &path);
private:
    vector3_t read_vector3(std::string line);
protected:
    std::vector<std::vector<vector3_t>> nuclei;
    const static uint NELEM = 100;
};

#endif
