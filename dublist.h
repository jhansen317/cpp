#ifndef DUBLIST_H_INC
#define DUBLIST_H_INC

#include <iostream>
#include <cstddef>

using namespace std;

class doublelist
{
    double * p;  // array of doubles
    size_t current_size;    // number of array positions filled
    size_t capacity;     // number of POSSIBLE array positions
    
    bool reallocate(size_t more);

public:

    
    doublelist(void) : p(NULL), current_size(0), capacity(0) { }
    
    doublelist(size_t caller_size) : p(new double[caller_size]), 
                  current_size(0), capacity(caller_size) 
    {
        capacity = p == NULL ? 0 : caller_size;             
    }
    
    doublelist(const doublelist & dl);
    
    ~doublelist(void) { delete [] p; p = NULL; }
    
    doublelist & operator=(const doublelist & dl);
    
    double operator[](const size_t index) const 
    {
        return (p == NULL || index >= current_size) ? 0.0 : p[index]; 
    }
    
    double & operator[](size_t index)  
    {   
        double num;
        num = 0.0;
        return (p == NULL || index >= current_size) ? num : p[index]; 
    }
    
    
    void insert_double(double num);
    
    double get_last(void) const { return p == NULL ? 0.0 : p[current_size-1]; } 
    
    void delete_last(void) 
    {
        if (p != NULL)
        {
            current_size--;
        }
        return;
    }
    
    size_t get_size(void) const { return p == NULL ? 0 : current_size; }

    void print(void) const;
    
};

istream & operator>>(istream & in, doublelist & dl);

ostream & operator<<(ostream & out, const doublelist & dl);




#endif
