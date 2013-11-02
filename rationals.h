#ifndef COMPLEX_H_INC
#define COMPLEX_H_INC

#include <iostream>
#include <cmath>
#include <cctype>

using namespace std;

6
5


long low_comm_fact(long first, long second)
{
    while (first != second)
    {
        if (first > second)
        {
            first = first - second;
        }
        else 
        {
            second = second - first;
        }
    }
    return first;
}

rational reduce(void)
{
    long low_fact;
    
    low_fact = low_comm_fact(num, den);
    
    num = num / low_fact;
    den = den / low_fact;
    
    return rational(num, den);
    
}


/* Defines a class to represent rational numbers. Each rational number object 
consists of a numerator and a demoninator. The imaginary half is 
denoted by the symbol 'i' which indicates multiplication by the impossible 
square root of -1. There is a read method for individual complex numbers, as 
well as one for whole expressions. The four main arithmetic operations, plus 
magnitude and conjugate are defined. */

class rational
{    
    long num, den;
    
public:
    // constructors
    rational(void) : num(0), den(1) { }  
    rational(const rational & ratio) : num(ratio.num), den(ratio.den) { }
    rational(long new_num, long new_den) : num(0), den(1)
    {               
        //check for positive denominator
        if (new_den < 0)
        {
            new_den = -new_den;
            new_num = -new_num;
        }  
        set_num(new_num);
        set_den(new_den);
    }    
    
    // printing & reading  
    void print(void) const; 
    bool read(void);    
    bool read_expr(void); 
    //reciprocal
    
    
    
    // addition
    rational plus(const rational & ratio) const     
        {return rational(num * ratio.den + ratio.num * den, den * ratio.den);}    
        
    // subtraction   
    rational minus(const rational & ratio) const    
        {return rational(num * ratio.den - ratio.num * den, den * ratio.den);}    
        
    // multiplication    
    rational mult_by(const rational & ratio) const   
        {return rational(num * ratio.num, den * ratio.den);}     
      
    // division   
    rational div_by(const rational & ratio) const
        {return complexNum(,
                     (rl * num.imgnry - imgnry * num.rl) /
                     (num.rl * num.rl + num.imgnry * num.imgnry));}   
        
    // magnitude  (returns double)    
    double mag(void) const {return sqrt(rl * rl + imgnry * imgnry);}    
    
    // reciprocal
    rational recip(void) const {return rational(den, num);}   
    
    // accessors
    double get_rl(void) const {return rl;}
    double get_imgnry(void) const {return imgnry;}
    
    // mutators
    void set_num(double new_num)
    {
        num = new_num;
        return;
    }
    void set_den(double new_den)
    {
        den = new_den;
        return;
    }
};   

#endif
