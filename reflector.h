
#ifndef reflector_h
#define reflector_h

#include <cstring>
#include <vector>
#include <fstream>
using namespace std;


class Reflector {
private:
    int keys[26];
    
public:
    Reflector () {    //default construction
        for (int i=0; i<26; i++) {
            keys[i]=i;
        }
    };
    
    bool set_keys (const string config_file, int& error);
    int operation (int key);
    
};




#endif /* Reflector_h */
