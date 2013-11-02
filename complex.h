#ifndef COMPLEX_H_INC
#define COMPLEX_H_INC

#include <iostream>
#include <cmath>
#include <cctype>

using namespace std;

/* Defines a type to represent complex numbers, expressed as the sum (or 
difference) of two numbers: one real and one imaginary. The imaginary half is 
denoted by the symbol 'i' which indicates multiplication by the impossible 
square root of -1. There is a read method for individual complex numbers, as 
well as one for whole expressions. The four main arithmetic operations, plus 
magnitude and conjugate are defined. */

class complexNum
{    
    double rl, imgnry;
    
public:
    // constructors
    complexNum(void) : rl(0.0), imgnry(0.0) { }  
    complexNum(const complexNum & num) : rl(num.rl), imgnry(num.imgnry){ }
    complexNum(double new_rl, double new_imgnry) : rl(0.0), imgnry(0.0)
    { 
        set_rl(new_rl);
        set_imgnry(new_imgnry);
    }    
    
    // printing & reading  
    void print(void) const; 
    bool read(void);    
    bool read_expr(void); // reads in an entire expression ie: 4+5i + 3+6i
    
    // addition
    complexNum plus(const complexNum & num) const     
        {return complexNum(rl + num.rl, imgnry + num.imgnry);}    
        
    // subtraction   
    complexNum minus(const complexNum & num) const    
        {return complexNum(rl - num.rl, imgnry - num.imgnry);}    
        
    // multiplication    
    complexNum mult_by(const complexNum & num) const   
        {return complexNum(rl * num.rl - imgnry * num.imgnry, 
                          rl * num.imgnry + imgnry * num.rl);}     
      
    // division   
    complexNum div_by(const complexNum & num) const
        {return complexNum((rl * num.rl + imgnry * num.imgnry) /
                     (num.rl * num.rl + num.imgnry * num.imgnry),
                     (rl * num.imgnry - imgnry * num.rl) /
                     (num.rl * num.rl + num.imgnry * num.imgnry));}   
        
    // magnitude  (returns double)    
    double mag(void) const {return sqrt(rl * rl + imgnry * imgnry);}    
    
    // conjugate
    complexNum conj(void) const {return complexNum(rl, -imgnry);}   
    
    // accessors
    double get_rl(void) const {return rl;}
    double get_imgnry(void) const {return imgnry;}
    
    // mutators
    void set_rl(double new_rl)
    {
        rl = new_rl;
        return;
    }
    void set_imgnry(double new_imgnry)
    {
        imgnry = new_imgnry;
        return;
    }
};   

#endif
