#include "nuclei.hpp"


Nuclei::Nuclei(const std::string &path){
    import_from(path);
}

// Prints a list of all coordinates of nuclear positions stored in nuclei[]
void Nuclei::print_nuclei(){
    printf("LIST OF ALL NUCLEAR POSITIONS:\n");
    for (uint Z = 0; Z < nuclei.size(); Z++) {
        if (nuclei[Z].size() != 0){
            printf("Nuclei with Z = %u:\n", Z);
        }
        for (uint mZ = 0; mZ < nuclei[Z].size(); mZ++) {
            vector3_t R = nuclei[Z][mZ];
            printf("(%lf,%lf,%lf)\n",R.v[0],R.v[1],R.v[2]);
        }
    }
}

// Saves new nuclear positions to memory
void Nuclei::save_as(const std::string &filename){
    std::ofstream outdata;
    outdata.open(filename);
    for (uint Z = 0; Z < nuclei.size(); Z++) {
        if (nuclei[Z].size() != 0){
            outdata<<"Z:"<<Z<<std::endl;
        }
        for (uint mZ = 0; mZ < nuclei[Z].size(); mZ++) {
            vector3_t R = nuclei[Z][mZ];
            outdata<<R.v[0]<<" "<<R.v[1]<<" "<<R.v[2]<<std::endl;
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

    nelectrons = 0;
    // Structure:
    // nuclei[Z][idx][x,y,z]
    uint Zval = 0;
    nuclei.resize(1); // Put in a dummy element so the damn thing doesn't
    // segfault immediately


    while (getline(indata, line)) {
        lineno++;
        if (line[0] == '#'){
            // Ignore comments
            continue;
        } else if (line[0] == 'Z'){
            // New Z value
            nelectrons += (Zval ==0 ) ? 0 : Zval*nuclei[Zval].size();
            Zval = stoi(line.substr(2));
            if (nuclei.size() <= Zval){
                nuclei.resize(Zval+1, std::vector<vector3_t>());
            }
        } else {
            // Assume we are reading 3 coordinates
            nuclei[Zval].push_back(read_vector3(line));
        }
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
            R.v[pos] = stod(cell);
            ++pos;
        } else {
            fprintf(stderr,"Found extra data!\n");
            // Ignore any superfluous data
        }
    }

    return R;
}