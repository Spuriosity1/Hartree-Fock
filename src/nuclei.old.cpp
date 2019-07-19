#include "nuclei.hpp"



Nuclei::Nuclei(){
    memset(len, 0, sizeof(uint)*NELEM);
}

Nuclei::Nuclei(const std::string &path){
    memset(len, 0, sizeof(uint)*NELEM);
    import_from(path);
}

Nuclei::~Nuclei(){
    // Odds of this working are exactly zero
    for (uint Z = 0; Z < NELEM; Z++) {
        free(nuclei[Z]);
    }
    free(nuclei);
}

// Prints a list of all coordinates of nuclear positions stored in nuclei[]
void Nuclei::print_nuclei(){
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

// Saves new nuclear positions to memory
void Nuclei::save_as(const std::string &filename){
    std::ofstream outdata;
    outdata.open(filename);
    for (uint Z = 0; Z < NELEM; Z++) {
        if (len[Z] != 0){
            outdata<<"Z:"<<Z<<std::endl;
        }
        for (uint mZ = 0; mZ < len[Z]; mZ++) {
            double* R = nuclei[Z]+3*mZ;
            outdata<<R[0]<<" "<<R[1]<<" "<<R[2]<<std::endl;
        }
    }
    outdata.close();
}


// Do this the old fashioned way
// This is quite possibly some of the worst code ever written
void Nuclei::import_from(const std::string &path){
    printf("Importing...\n");
    std::ifstream indata;
    indata.open(path);
    if (!indata.is_open()){
        fprintf(stderr, "Failed to load file `%s` !\n",path.c_str());
        return;
    }

    std::string line;
    uint lineno = 0;
    nuclei = (elements_t*) malloc(sizeof(elements_t) * NELEM);
    memset(nuclei, (int) NULL, NELEM*sizeof(elements_t*));

    nelectrons = 0;
    // Structure:
    // nuclei[Z][idx][x,y,z]
    std::vector<vector3_t> values;
    uint Zval = 0;
    bool nempty = false;
    while (getline(indata, line)) {
        lineno++;

        #ifndef NDEBUG
        fprintf(stderr, "DEBUG: line %u\n",lineno);
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


// Reads 3 Euclidean coords like 1 2 -0.222e-4 from a std::string line,
// returns as vector3_t
vector3_t Nuclei::read_vector3(std::string line){
    std::stringstream lineStream(line);
    std::string cell;

    uint pos=0;
    vector3_t R;

    while (getline(lineStream, cell, ' ')) {
        if (pos < 3){
            R.vals[pos] = stod(cell);
            ++pos;
        } else {
            fprintf(stderr,"Found extra data!\n");
            // Ignore any superfluous data
        }
    }

    return R;
}

// Utility function to allocate and store vector of vector3_t in nuclei
void Nuclei::store_vector(uint Z, std::vector<vector3_t> &v){
    nuclei[Z] = (elements_t) malloc(3*v.size()*sizeof(elements_t));
    len[Z] = v.size();

    for (uint mZ = 0; mZ < v.size(); mZ++) {
        for (size_t j = 0; j < 3; j++) {
            nuclei[Z][3*mZ+j] = v[mZ].vals[j];
        }
    }
}
