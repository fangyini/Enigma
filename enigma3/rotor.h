
#ifndef rotor_h
#define rotor_h

#include <vector>
#include <cstring>
#include <fstream>
using namespace std;

class Rotor {
private:
    int keys[26];
    int rev_keys[26];
    vector <int> notch;
    int offset;
    
public:
    Rotor () {
        for (int i=0; i<26; i++) {
            rev_keys[i]=-1;
            keys[i]=-1;
        }
        offset=0;
    };
    bool set_keys (const string config_file, int position, int& error);
    int reverse_operation (int key);
    int operation (int key);
    bool check_notch ();
    void rotate ();
};


#endif /* Rotor_h */
