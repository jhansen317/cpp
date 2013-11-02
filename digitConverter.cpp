#include <iostream>
#include <string>
#include <cstdlib>
#include <climits>
#include "digitConverter.h"

using namespace std;

#ifndef DCONVERT_H_INC

#define DCONVERT_H_INC


string convertDigit(short place, short number, char one, char five, char ten)
{
    
    string returnString;
    short i;
    
    returnString.clear();
    
    number = number/place % 10;
    
    if (number > 0 && number < 4 || number > 4 && number < 9 )
    {  
        for(i = 1; i <= number % 5; i++)
        {
        returnString.insert(returnString.begin(), one);
        }
       
        if (number >= 5 && number < 9)
        {                
            returnString.insert(returnString.begin(), five); 
        }
    }
    else if (number == 4)
    {                
        returnString.insert(returnString.begin(), five); 
        returnString.insert(returnString.begin(), one);
    }
    else if (number == 9)
    {                      
        returnString.insert(returnString.begin(), ten);
        returnString.insert(returnString.begin(), one);
    }
    
    return returnString;   
}

#endif
