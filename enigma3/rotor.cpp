#include "rotor.h"
#include "errors.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <fstream>
#include "helper.h"
using namespace std;



bool Rotor::set_keys (const string config_file, int position, int& error) {
    
    vector<int> config_array;

    if (!read_file(config_file, config_array, error)){
        if (error==NON_NUMERIC_CHARACTER) {
            cerr<<"Non-numeric character for mapping in rotor file "<<config_file<<endl;
        }
        return false;
    }
    
    if (config_array.size()<26) {
        cerr<<"Not all inputs mapped in rotor file: "<<config_file<<endl;
        error=INVALID_ROTOR_MAPPING;
        return false;
    }
    
    offset+=position;    //set the offset according to the beginning position

    
    for (int i=0; i<int(config_array.size()); i++) {
        if (i<26) {
            if (config_array[i]<0 || config_array[i]>25) {
                error=INVALID_INDEX;
                return false;
            }
            keys[i] = config_array[i];
            if (rev_keys[keys[i]]!=-1) {  //If the mapping is repeated, the value has already been changed
                cerr<<"Invalid mapping of input "<<i<<" to output "<<keys[i]<<" (output "<<keys[i]<<" is already mapped to from input "<<rev_keys[keys[i]]<<") "<<endl;
                error=INVALID_ROTOR_MAPPING;
                return false;
            }
            rev_keys[keys[i]]=i;
        }
        else
            notch.push_back(config_array[i]);  //Store the values in 'notch' vector when the index is larger than 25
    }
    return true;
}


int Rotor::reverse_operation(int key) {
    return (rev_keys[(key+offset)%26]-offset+26)%26;  //Ensure that neither index or output is more than 25 and less than 0
    
}

int Rotor::operation(int key) {
    return (keys[(key+offset)%26]-offset+26)%26;
}

bool Rotor::check_notch() {
    for (int i=0; i<int(notch.size()); i++) {  //check if the letter in the absolute position of this rotor is the same as one of notch value
        if (notch[i]==offset) {
            return true;
        }
    }
    return false;
}

void Rotor::rotate () {
    offset = (offset+1)%26;  //The offset increases as the rotor rotates
}

