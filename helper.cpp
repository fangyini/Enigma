
#include "helper.h"
#include "errors.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <string>
#include <set>
using namespace std;

bool read_file (const string file_name, vector<int>& content, int& error){
    ifstream input;
    string str;
    input.open(file_name);
    if (input.fail()) {
        error=ERROR_OPENING_CONFIGURATION_FILE;
        return false;
    }
    input>>str;
    while (!input.eof()) {
        if (!is_numerical(str)) {
            error=NON_NUMERIC_CHARACTER;
            return false;
        }
        content.push_back(stoi(str));  //Convert the string to a number using 'stoi'
        input>>str;
    }
    return true;
}

bool no_repeated (vector<int> vec) {  //No repeated elements are allowed in a set variable
    set<int> set(vec.begin(), vec.end());
    if (vec.size()==set.size()) {
        return true;
    }
    else
        return false;
}

bool is_numerical (const string str) {
    stringstream sin(str);
    double t;
    char p;
    if (!(sin>>t)) {  //Check if 'str' can be read as a double number
        return false;
    }
    if (sin>>p) {  //If 'str' can be read as a charater, then it is not numerical
        return false;
    }
    else
        return true;
}

bool is_valid_index (int index) {
    if (index<0 || index>25) 
        return false;
    return true;
}

bool no_repeated_rotor (vector<int> vec) {
    set<int> set(vec.begin(), vec.begin()+25);
    if (set.size()!=26) {
        return true;
    }
    else
        return false;
}

bool file_check (const char *files[], int num){
    bool check=false;
    if (keyword_check(files[1], "pb") && keyword_check(files[2], "rf")) { //Check if any file is missing
        check=true;
        if (num>4) {  //Check the position file and rotor files
            if (!keyword_check(files[num-1], "pos"))
                check=false;

            if (check==true) {
                for (int i=3; i<num-3; i++) {
                    if (!keyword_check(files[i], "rot"))
                        check=false;
                }
            }
        }
    }
    return check;
}

bool keyword_check (const string s, const string keyword){  //Check if the string 'keyword' is included in the string 's'
    if (s.find(keyword)!=string::npos){
        return true;
    }
    else
        return false;
}
