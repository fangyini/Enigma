#include "enigma.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include "helper.h"
#include "errors.h"
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;


//Set all the keys in the plugboard, reflector and rotors according to the input files
bool Enigma::set (const string plug_file, const string refl_file, const vector<string> rot_config_file, const string rot_pos_file, int rot_num, int& error) {
    
    vector<int> pos;
    
    if(!plugboard.set_keys(plug_file, error) || !reflector.set_keys(refl_file, error))
        return false;
    
    if (rot_config_file.size()!=0) {  //check if there is no rotor
        if(!read_file(rot_pos_file, pos, error)){
            if (error==NON_NUMERIC_CHARACTER) {
                cerr<<"Non-numeric character in rotor positions file "<<rot_pos_file<<endl;
            }
            return false;
        }
        
        if (rot_num>int(pos.size())) {  //Compare the number of rotors and the number of positions in the position file
            cerr<<"No starting position for rotor ";
            for (int i=0; i<rot_num-int(pos.size()); i++) {
                cerr<<i<<" ";
            }
            cerr<<"in rotor position file: "<<rot_pos_file<<endl;
            error = NO_ROTOR_STARTING_POSITION;
            return false;
        }
        
        Rotor ini_rotor;
        reverse(pos.begin(), pos.end());
        for (int i=0; i<rot_num; i++) {    //set keys of every rotor
            rotors.push_back(ini_rotor);
            if(!rotors[i].set_keys(rot_config_file[i], pos[i], error))
                return false;
        }
    }
    
    return true;
}

//Rotate the right hand rotor, and check if the absolute position reaches the notch
void Enigma::rotor_rotate() {
    int i=0;
    rotors[0].rotate();
    while (i<int(rotors.size())-1) {
        if (rotors[i].check_notch()==true) {
            rotors[i+1].rotate();
            i++;
        }
        else
            break;
    }
}

char Enigma::operation(char key) {  //Output the encrypted character
    int output, i=0;
    output=plugboard.operation(key-'A');  //Convert the character into the letter index by subtracting 'A'
    
    if (rotors.size()!=0) {  //check if there is no rotor
        rotor_rotate();    //rotate according to notch
        for (i=0; i<int(rotors.size()); i++) {  //Pass the character in rotors from right to left
            output=rotors[i].operation(output);
        }
    }
    
    output=reflector.operation(output);
    
    if (rotors.size()!=0) {  //Pass the character in rotors from left to right
        for (i=(int)(rotors.size()-1); i>=0; i--) {
            output=rotors[i].reverse_operation(output);
        }
    }
    
    output=plugboard.operation(output);
    return letters[output];  //Output the letter given the letter index
}
