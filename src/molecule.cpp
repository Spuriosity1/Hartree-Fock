#include "molecule.hpp"

Molecule::Molecule(){
    for (size_t i = 0; i < NELEM; i++) {
        len[i]=0;
    }
}

Molecule::Molecule(const string &path){
    for (size_t i = 0; i < NELEM; i++) {
        len[i]=0;
    }
    import_from(path);
}

Molecule::~Molecule(){
    // Odds of this working are exactly zero
    for (uint Z = 0; Z < NELEM; Z++) {
        free(nuclei[Z]);
    }
    free(nuclei);
}

void Molecule::print(){
    printf("LIST OF ALL NUCLEAR POSITIONS:\n");
    for (uint Z = 0; Z < NELEM; Z++) {
        if (len[Z] != 0){
            printf("Nuclei with Z = %u:\n", Z);
        }
        for (uint mZ = 0; mZ < len[Z]; mZ++) {
            double* R = nuclei[Z]+3*mZ;
            printf("(%lf,%lf,%lf)\n",R[0],R[1],R[2]);
        }
    }
}

void Molecule::save_as(const string &filename){
    ofstream outdata;
    outdata.open(filename);
    for (uint Z = 0; Z < NELEM; Z++) {
        if (len[Z] != 0){
            outdata<<"Z:"<<Z<<endl;
        }
        for (uint mZ = 0; mZ < len[Z]; mZ++) {
            double* R = nuclei[Z]+3*mZ;
            outdata<<R[0]<<" "<<R[1]<<" "<<R[2]<<endl;
        }
    }
    outdata.close();
}


// Do this the old fashioned way
// This is quite possibly some of the worst code ever written
void Molecule::import_from(const string &path){
    ifstream indata;
    indata.open(path);
    string line;
    uint lineno = 0;

    nuclei = (double **) malloc(sizeof(double *) * NELEM);
    memset(nuclei, (int) NULL, NELEM);

    nelectrons = 0;
    // Structure:
    // nuclei[Z][idx][x,y,z]
    vector<vector3_t> values;
    uint Zval = 0;
    bool nempty = false;
    while (getline(indata, line)) {
        lineno++;

        #ifdef DEBUG
        printf("DEBUG: line %u\n",lineno);
        #endif

        if (line[0] == '#'){
            // Ignore comments
            continue;
        } else if (line[0] == 'Z'){
            // New Z value
            store_vector(Zval,values);
            nelectrons += Zval*values.size();
            values.clear();
            Zval = stoi(line.substr(2));
        } else {
            // Assume we are reading 3 coordinates
            values.push_back(read_vector3(line));
            nempty = true;
        }
    }

    if (nempty){
        store_vector(Zval,values);
    }
}


// Reads 3 Euclidean coords like 1 2 -0.222e-4 from a std::string line
vector3_t read_vector3(string line){
    stringstream lineStream(line);
    string cell;

    uint pos=0;
    vector3_t R;

    while (getline(lineStream, cell, ' ')) {
        if (pos < 3){
            R.vals[pos] = stod(cell);
            ++pos;
        } else {
            // Ignore any superfluous data
            fprintf(stderr, "Found extra data at line %u\n", lineno);
        }
    }

    return R;
}


void Molecule::store_vector(uint Z, vector<vector3_t> v){
    nuclei[Z] = (double *) malloc(3*v.size()*sizeof(double *));
    len[Z] = v.size();

    for (uint mZ = 0; mZ < v.size(); mZ++) {
        for (size_t j = 0; j < 3; j++) {
            nuclei[Z][3*mZ+j] = v[mZ].vals[j];
        }
    }
}
