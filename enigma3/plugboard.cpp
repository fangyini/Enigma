#include "plugboard.h"
#include "errors.h"
#include "helper.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <fstream>
using namespace std;

bool Plugboard::set_keys(const string config_file, int& error) {
    
    vector<int> config_array;
    
    if (!read_file(config_file, config_array, error)){
        if (error==NON_NUMERIC_CHARACTER) {
            cerr<<"Non-numeric character in plugboard file "<<config_file<<endl;
        }
        return false;
    }
    
    if (config_array.size()%2!=0) {   //check if the file contains an odd number of numbers
        cerr<<"Incorrect number of parameters in plugboard file "<<config_file<<endl;
        error=INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
        return false;
    }
    
    if (!no_repeated(config_array)) {  //check if the file attempts to connect a contact with itself, or with more than one other contact (both of conditions equal to 'if there are repeated elements'
        error=IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
        return false;
    }
    
    for (int i=0; i<int(config_array.size()); i+=2) {
        if (!is_valid_index(config_array[i]) || !is_valid_index(config_array[i+1])) {
            error=INVALID_INDEX;
            return false;
        }
        swap(keys[config_array[i]],keys[config_array[i+1]]);  //Swap two elements using 'swap' function
    }
    return true;
}

int Plugboard::operation(int key) {
    return keys[key];
}

