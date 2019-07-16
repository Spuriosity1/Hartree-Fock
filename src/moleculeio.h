#include <string>
#include <fstream>
#include <vector>

#ifndef HF_MOLECULEIO_H
#define HF_MOLECULEIO_H

// Highest atomic number we need
// Not the most general prescription - however, consider how large the need for
// ununoctium is in your biology
#define NELEM 100

#define FORMAT_SPECIFICATION "Syntax:\n\
Z 5:\n\
100,22,33\n\
22,33,55\n\
Z 12:\n\
3,4,-2\n\n\
(X, Y, Z) Positions in Angstrom"

/* Syntax:
Z 5:
100,22,33
22,33,55
Z 12:
3,4,-2

(X Y Z) Positions in Angstrom
*/
using namespace std;

// Wrapper for convenience
typedef struct {
    double vals[3];
} vector3_t;

// Do this the old fashioned way
// This is quite possibly some of the worst code ever written
double*** import(const string &filename){
    ifstream indata;
    indata.open(path);
    string line;
    uint lineno = 1;

    double ***positions = (double **) malloc(sizeof(double *) * NELEM);
    memset(positions, NULL, NELEM);

    // Structure:
    // positions[Z][idx][x,y,z]
    vector<vector3_t> values;
    uint Zval = 0;
    while (getline(indata, line)) {
        lineno++;
        if (line[0] == '#'){
            // Ignore comments
            continue;
        } else if (line[0] == 'Z'){
            // New Z value
            positions[Zval] = malloc(values.size()*sizeof(vector3_t));
            for (uint mZ = 0; mZ < values.size(); mZ++) {
                for (size_t j = 0; j < 3; j++) {
                    positions[Zval][mZ][j] = values[mZ].vals[j];
                }
            }
            values.clear();
            Zval = stoi(line.substr(2));
        } else {
            // Assume we are reading 3 coordinates
            stringstream lineStream(line);
            string cell;

            unit pos=0;
            vector3_t R;

            while (getline(lineStream, cell, ',')) {
                if (pos < 3){
                    R.vals[pos] = stod(cell);
                    ++pos;
                } else {
                    // Ignore any superfluous data
                    cerr << "Found extra data at line " << lineno << endl;
                }
            }
            values.push_back(R);
        }
    }
}



#endif
