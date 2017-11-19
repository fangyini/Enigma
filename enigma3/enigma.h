

#ifndef enigma_h
#define enigma_h

#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include <vector>
#include <cstring>
using namespace std;


class Enigma {
private:
    Reflector reflector;
    Plugboard plugboard;
    vector<Rotor> rotors;
    
public:
    Enigma() {};
    bool set (const string plug_file, const string refl_file, const vector<string> rot_config_file, const string rot_pos, int rot_num, int& error);
    char operation (char key);
    void rotor_rotate ();
    //~Enigma();
};




#endif /* Enigma_h */
