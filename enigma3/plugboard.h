

#ifndef plugboard_h
#define plugboard_h

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <set>
using namespace std;


class Plugboard {
private:
    int keys[26];
    
public:
    Plugboard () {    //default construction
        for (int i=0; i<26; i++) {
            keys[i]=i;
        }
    };
    
    bool set_keys (const string config_file, int& error);
    int operation (int key);
    
};


#endif /* Plugboard_h */
