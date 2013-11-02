#include <iostream>
#include <cmath>
#include <climits>
#include <cctype>
#include "complex.h"

using namespace std;

void complexNum::print(void) const // prints numbers with appropriate notation
{
    if (imgnry > 0)
    {
        cout << rl << '+' << imgnry << 'i';
    }
    else if (fabs(imgnry) <= pow(10, -6))
    {
        cout << rl;
    }
    else
    {
        cout << rl << imgnry << 'i';
    }
    return;
}

/* Reads complex numbers, with a check for correct operator between real and 
imaginary parts. Numeric input failure is reported to the caller, but dealing
with it and re-prompting is up to the caller. */

bool complexNum::read(void) 
{
    char sign, t;
    bool success;
    
    cin >> rl >> sign >> imgnry >> t;
    
    success = !cin.fail();
    
    if (sign == '-')
    {
        imgnry = -imgnry;
    }
    else if (sign != '-' && sign != '+')
    {
        success = false;
        cout << "\nUnrecognized operator!!";
    }
    
    return success; 
}

/* Reads in an entire expression, */

bool complexNum::read_expr(void)
{
    bool success;
    complexNum num1;
    complexNum num2;
    complexNum result;
    char oprtr;
    
    num1.read();   
    cin >> oprtr;  
    num2.read();
    
    success = !cin.fail();
    
    switch (oprtr)
    {
        case '+':
        result = num1.plus(num2);
        break;
        case '-':
        result = num1.minus(num2);
        break;
        case '*':
        result = num1.mult_by(num2);
        break;
        case '/':
        result = num1.div_by(num2);
        break;
        default:
        cout << "\nInvalid Operator!"
             << "\nSupported operators are '+', '-', '*', and '/'.";
        success = false;    
    }
    
    rl = result.get_rl();
    imgnry = result.get_imgnry();
    
    return success;
}
