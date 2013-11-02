#include "dublist.h"
#include <cstddef>
#include <iostream>
#include <climits>

using namespace std;


doublelist::doublelist(const doublelist & dl) 
          : p(new double[dl.capacity]), 
            current_size(dl.current_size),
            capacity(dl.capacity)
{
    if (p != NULL)
    {
        for (size_t i=0; i != current_size; i++)
        {
            p[i] = dl.p[i];
        }
    }
    else
    {
        current_size = capacity = 0;
    }
}

doublelist & doublelist::operator=(const doublelist & dl)
{
    if ( &dl != this )
    {
        delete [] p;
        
        p = new double[dl.capacity];
        
        if (p != NULL)
        {
            capacity = dl.capacity;
            current_size = dl.current_size;
            for(size_t i=0; i != current_size; i++)
            {
                p[i] = dl.p[i];
            }
        }
        else
        {
            current_size = capacity = 0;
        }
    }
    return *this;
}

bool doublelist::reallocate(size_t more)
{
    double * pnew;
    bool okay = false;
    pnew = new double [capacity + more];
    if (pnew != NULL)
    {
        okay = true;
        for (size_t i=0; i != current_size; i++)
        {
            pnew[i] = p[i];
        }
        delete [] p;
        p = pnew;
        pnew = NULL;
        capacity += more;
    }
    return okay; 
}


void doublelist::insert_double(double num)
{
    if (current_size == capacity)
    {
        if (reallocate(p == NULL ? 2 : capacity))
        {
            p[current_size++] = num;
        }
        else
        {
            cerr << "\nERROR: MEMORY ALLOCATION FAILED";
        }
    }
    else
    {
        p[current_size++] = num;
    }
    return;
}


void doublelist::print(void) const
{
    size_t i;
    for (i = 0; i < current_size; i++)
    {
        cout << p[i] << ' ';
    }
    return;
}

istream & operator>>(istream & in, doublelist & dl)
{
    double num;
    in >> num;
    while (in.peek() != '\n' && !in.fail())
    {
        dl.insert_double(num);
        in >> num;
    }    
    in.clear();
    in.ignore(INT_MAX, '\n');

    return in;
}


ostream & operator<<(ostream & out, const doublelist & dl)
{
    size_t i;
    for (i=0; i != dl.get_size(); i++)
    {
        out << dl[i] << ' ';
    }
    return out;
}

