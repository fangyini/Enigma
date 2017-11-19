#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <string>
#include <fstream>
#include "errors.h"
#include "enigma.h"
#include "helper.h"
using namespace std;

int main(int argc, const char * argv[]) {
    
    if (argc<3 || !file_check(argv, argc)) {  //Check if the number of files is less than three, and check if any of '.pf' and '.rf' files are missing
        cerr<<"usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?"<<endl;
        return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }
    
    vector<string> rot_config_file;
    
    int i=0;
    if (argc>4) {  //Check if there is no rotor
        i=argc-2;
        while (i>=argc-4) {
            rot_config_file.push_back(argv[i]);  //Store the file names in a reverse order
            i--;
        }
    }
    
    int error=0;
    Enigma *enigma = new Enigma();
    if(!enigma->set(argv[1], argv[2], rot_config_file, argv[argc-1], argc-4, error)){  //Set configuration
        return error;
    }

    char input;
    cin>>input;
    while (cin) {
        if (input<'A' || input>'Z') {  //Check if the input character is an upper letter
            cerr<<input<<" is not a valid input character (input characters must be upper case letters A-Z)!"<<endl;
            return INVALID_INPUT_CHARACTER;
        }
        cout<<enigma->operation(input);
        cin>>input;
    }
    
    delete enigma;
    
    return 0;
}
