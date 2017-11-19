#include "reflector.h"
#include "errors.h"
#include <vector>
#include <cstring>
#include <fstream>
#include "helper.h"
#include "plugboard.h"
using namespace std;



bool Reflector::set_keys(const string config_file, int& error) {
    vector<int> config_array;
    
    if (!read_file(config_file, config_array, error)){
        if (error==NON_NUMERIC_CHARACTER) {
            cerr<<"Non-numeric character in reflector file "<<config_file<<endl;
        }
        return false;
    }
    
    if (config_array.size()%2==0) {
        if (config_array.size()<26) {
            cerr<<"Insufficient number of mappings in reflector file: "<<config_file<<endl;
            error=INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
            return false;
        }
        if (config_array.size()>26) {
            cerr<<"Incorrect (even) number of mappings in reflector file: "<<config_file<<endl;
            error=INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
            return false;
        }
    }
    
    if (config_array.size()%2!=0 && config_array.size()) {
        cerr<<"Incorrect (odd) number of parameters in reflector file "<<config_file<<endl;
        error=INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
        return false;
    }
    
    if (!no_repeated(config_array)) {  //check if the file attempts to map an input to itself or pair each index with more than one other
        error=INVALID_REFLECTOR_MAPPING;
        return false;
    }
    
    for (int i=0; i<int(config_array.size()); i+=2) {
        if (!is_valid_index(config_array[i]) || !is_valid_index(config_array[i+1])) {
            error=INVALID_INDEX;
            return false;
        }
        swap(keys[config_array[i]],keys[config_array[i+1]]);
    }
    return true;
}

int Reflector::operation(int key) {
    return keys[key];
}
