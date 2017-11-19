
#ifndef helper_h
#define helper_h

#include <stdio.h>
#include "helper.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <set>
using namespace std;

const string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

bool no_repeated (vector<int> vec);
bool is_numerical (const string str);
bool is_valid_index (int index);
bool no_repeated_rotor (vector<int> vec);
bool file_check (const char *files[], int num);
bool keyword_check (const string s, const string keyword);
bool read_file (const string file_name, vector<int>& content, int& error);



#endif /* helper_hpp */
