#include <iostream>
#include <string>
#include "RandLetter.h"

using namespace std;

int main(void)
{
    srand(time(NULL));
    string randumb; 
    size_t ransize = 10;
    char randchar;

    randchar = RandLetter();
    cout << "A random character is: " << randchar << endl;

    randumb = RandString(ransize);
    
    cout << "A random string is: " << randumb << endl;
    return 0;
}
