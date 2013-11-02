#ifndef STREXTRA_H_INC
#define STREXTRA_H_INC

#include <cstring>
#include <iostream>
#include <climits>

using namespace std;

// char version
short find(const char str[], char c, short index = 0);

// string version
short find(const char str[], char substr[], short index = 0, 
                                        bool caseSense = false);


// nice input
void get_line(char s[], const long max);

#endif
